#include "AudioEngine.h"
#include <stdio.h>
#include <math.h>

#include <utility>
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
    m_currentSong = std::move(song);
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

        processRow(m_currentRow, Channel::Pulse1);
        processRow(m_currentRow, Channel::Pulse2);
        processRow(m_currentRow, Channel::Triangle);
    }
}

void AudioEngine::processRow(int row, int channel)
{
    const Note& note = m_currentSong->getPattern().getNote(row, channel);

    if (note.key == NONE) {
        return;
    }

    const float freq = NOTE_OCTAVE[note.oct] * powf(2, note.key / 12.f);
    const auto timer =
        static_cast<uint16_t>((1789773 / ((channel == Channel::Triangle ? 32.f : 16.f) * freq)) - 1.0);

    uint8_t status =  s_apu.readStatusRegister();
    uint8_t channelFlag = 0;
    switch (channel) {
    case Channel::Pulse1: channelFlag = 0x01; break;
    case Channel::Pulse2: channelFlag = 0x02; break;
    case Channel::Triangle: channelFlag = 0x04; break;
    default: break;
    }

    if (note.key == REST) {
        s_apu.writeStatusRegister(status &= ~channelFlag);
        return;
    }

    if (channel == Channel::Pulse1) {
        s_apu.writeStatusRegister(status | channelFlag);
        s_apu.writeRegister(0x4000, 0xff);                // Volume Envelope
        s_apu.writeRegister(0x4001, 0x00);                // Sweep
        s_apu.writeRegister(0x4002, timer & 0xFF);        // Frequency low
        s_apu.writeRegister(0x4003, (timer >> 8) & 0x07); // Frequency high + trigger
    }
    else if (channel == Channel::Pulse2) {
        s_apu.writeStatusRegister(status | channelFlag);
        s_apu.writeRegister(0x4004, 0b01111111);                // Volume Envelope
        s_apu.writeRegister(0x4005, 0x00);                // Sweep
        s_apu.writeRegister(0x4006, timer & 0xFF);        // Frequency low
        s_apu.writeRegister(0x4007, (timer >> 8) & 0x07); // Frequency high + trigger
    }
    else if (channel == Channel::Triangle) {
        s_apu.writeStatusRegister(status | channelFlag);
        s_apu.writeRegister(0x4008, 0xff);                // Volume Envelope
        s_apu.writeRegister(0x400A, timer & 0xFF);        // Frequency low
        s_apu.writeRegister(0x400B, (timer >> 8) & 0x07); // Frequency high + trigger
    }
}

void AudioEngine::noteOn(Key key, int oct)
{
    const float freq = NOTE_OCTAVE[oct] * powf(2, key / 12.f);
    const auto timer =
        static_cast<uint16_t>((1789773 / (32 * freq)) - 1.0);

    const uint8_t status =  s_apu.readStatusRegister();

    s_apu.writeStatusRegister(status | 0x04);
    s_apu.writeRegister(0x4008, 0xff);                // Volume Envelope
    s_apu.writeRegister(0x400A, timer & 0xFF);        // Frequency low
    s_apu.writeRegister(0x400B, (timer >> 8) & 0x07); // Frequency high + trigger
}

void AudioEngine::noteOff()
{
    uint8_t status =  s_apu.readStatusRegister();
    s_apu.writeStatusRegister(status &= ~0x04);
}

AudioEngine::AudioEngine()
{
}

AudioEngine::~AudioEngine()
{
}
