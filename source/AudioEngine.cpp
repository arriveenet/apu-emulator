#include "AudioEngine.h"
#include <stdio.h>
#include "Tracker.h"

AudioEngine AudioEngine::s_instance;
ALCdevice* AudioEngine::s_pALDevice = nullptr;
ALCcontext* AudioEngine::s_pALContext = nullptr;
Apu AudioEngine::s_apu;
AudioStream AudioEngine::s_audioStream;

AudioEngine* AudioEngine::getInstance()
{
    return &s_instance;
}

bool AudioEngine::init()
{
    bool result = false;
    do {
        s_pALDevice = alcOpenDevice(nullptr);

        if (s_pALDevice != nullptr) {
            s_pALContext = alcCreateContext(s_pALDevice, nullptr);
            alcMakeContextCurrent(s_pALContext);

            ALenum alError = alGetError();
            if (alError != AL_NO_ERROR) {
                break;
            }

            const char* vender = alGetString(AL_VENDOR);
            const char* version = alGetString(AL_VERSION);

            printf("OpenAL initialization successful. vender: %s, version: %s\n", vender,
                         version);

            result = true;
        }
        else {
            printf("OpenAL initialization failed. alcOpenDevice() failed.");
            break;
        }
    } while (false);

    // Initialize audio stream
    s_audioStream.setApu(&s_apu);
    s_apu.writeStatusRegister(0x04);
    s_audioStream.play();

    return result;
}

void AudioEngine::terminate()
{
    if (s_pALContext != nullptr) {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(s_pALContext);
        s_pALContext = nullptr;
    }

    if (s_pALDevice != nullptr) {
        alcCloseDevice(s_pALDevice);
        s_pALDevice = nullptr;
    }
}

void AudioEngine::play(std::shared_ptr<Song> song)
{
    m_isPlaying = true;
    m_currentSong = song;
    m_currentRow = 0;
}

void AudioEngine::stop()
{
    m_isPlaying = false;
    m_currentSong = nullptr;
    m_currentRow = 0;
    m_tickCounter = 0;
    s_apu.writeStatusRegister(0x00); // Stop all channels
}

void AudioEngine::reset()
{
    m_currentRow = 0;
    m_tickCounter = 0;
    s_apu.writeStatusRegister(0x00); // Stop all channels
}

void AudioEngine::update()
{
    if (!m_currentSong || !m_isPlaying) {
        return;
    }

    // Advance tick counter
    m_tickCounter++;

    if (m_tickCounter >= m_currentSong->getSpeed()) {
        m_tickCounter = 0;
        m_currentRow++;

        processRow(m_currentRow);
    }
}

void AudioEngine::processRow(int row)
{
    Note& note = m_currentSong->getPattern().getNote(row, 0);

    if (note.key == NONE) {
        return;
    }

    float freq = NOTE_OCTAVE[note.oct] * powf(2, note.key / 12.f);
    uint16_t timer = static_cast<uint16_t>((1789773 / (8.0 * freq)) - 1.0);
    if (timer < 2)
        timer = 2;

    if (note.key == REST) {
        return;
    }

    s_apu.writeRegister(0x4000, 0xff);                // Volume Envelope
    s_apu.writeRegister(0x4001, 0x00);                // Sweep
    s_apu.writeRegister(0x4002, timer & 0xFF);        // Frequency low
    s_apu.writeRegister(0x4003, (timer >> 8) & 0x07); // Frequency high + trigger
}

AudioEngine::AudioEngine()
{
}

AudioEngine::~AudioEngine()
{
}
