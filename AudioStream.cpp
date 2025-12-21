#include "AudioStream.h"
#include "Apu.h"
#include <AL/alext.h>
#include <string.h>
#include <stdio.h>
#include <chrono>
#include <algorithm>


AudioStream::AudioStream()
    : m_source(0)
    , m_buffers{0}
    , m_apu(nullptr)
    , m_audioBuffer{0}
    , m_cpuRemainder(0.0)
    , m_updateThread()
{
}

AudioStream::~AudioStream()
{
    destroy();

    alDeleteSources(1, &m_source);
    alDeleteBuffers(NUM_BUFFERS, m_buffers);
}

void AudioStream::setApu(APU* apu)
{
    m_apu = apu;
}

void AudioStream::destroy()
{
    m_isDesroy = true;
    if (m_updateThread.joinable()) {
        m_updateThread.join();
    }
}

void AudioStream::play()
{
    if (m_apu == nullptr) {
        printf("AudioStream::play() - APU not set!\n");
        return;
    }

    alGenSources(1, &m_source);
    alGenBuffers(NUM_BUFFERS, m_buffers);

    alSourcef(m_source, AL_GAIN, 0.5f);
    alSourcef(m_source, AL_PITCH, 1.0f);
    alSourcei(m_source, AL_LOOPING, AL_FALSE);

    for (int i = 0; i < NUM_BUFFERS; i++) {
        fillBuffer();
        alBufferData(m_buffers[i], AL_FORMAT_MONO16, m_audioBuffer,
                     BUFFER_SAMPLES * sizeof(int16_t),
                     SAMPLE_RATE);
    }

    alSourceQueueBuffers(m_source, NUM_BUFFERS, m_buffers);

    m_updateThread = std::thread(&AudioStream::update, this);

    alSourcePlay(m_source);
}

void AudioStream::update()
{
    while (!m_isDesroy) {
        ALint processed = 0;
        alGetSourcei(m_source, AL_BUFFERS_PROCESSED, &processed);

        if (processed == 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            continue;
        }

        while (processed-- > 0) {
            ALuint buffer;
            alSourceUnqueueBuffers(m_source, 1, &buffer);

            fillBuffer();

            alBufferData(buffer, AL_FORMAT_MONO16, m_audioBuffer,
                         BUFFER_SAMPLES * sizeof(int16_t),
                         SAMPLE_RATE);
            alSourceQueueBuffers(m_source, 1, &buffer);
        }

        ALint state;
        alGetSourcei(m_source, AL_SOURCE_STATE, &state);
        if (state != AL_PLAYING) {
            alSourcePlay(m_source);
        }
    }
}

void AudioStream::fillBuffer()
{
    if (m_apu == nullptr) {
        memset(m_audioBuffer, 0, sizeof(m_audioBuffer));
        return;
    }

    for (int i = 0; i < BUFFER_SAMPLES; i++) {
        m_cpuRemainder += CPU_FREQUENCY / static_cast<double>(SAMPLE_RATE);
        while (m_cpuRemainder >= 1.0f) {
            m_apu->clock();
            m_cpuRemainder -= 1.0f;
        }
        const float s = m_apu->getOutput();
        int16_t pcm = static_cast<int16_t>(std::clamp(s, -1.0f, 1.0f) * 32767.0f);
        m_audioBuffer[i] = pcm;
    }
}
