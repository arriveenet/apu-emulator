#pragma once
#include <AL/al.h>
#include <thread>

class Apu;

class AudioStream {
public:
    static constexpr int NUM_BUFFERS = 4;
    static constexpr int BUFFER_SAMPLES = 512;
    static constexpr int SAMPLE_RATE = 44100;
    static constexpr double CPU_FREQUENCY = 1789773.0;

    AudioStream();
    ~AudioStream();

    void setApu(Apu* apu);

    void destroy();

    void play();

    void update();

private:
    void fillBuffer();

    ALuint m_source;
    ALuint m_buffers[NUM_BUFFERS];
    Apu* m_apu;
    int16_t m_audioBuffer[BUFFER_SAMPLES];
    double m_cpuRemainder = 0.0;
    std::thread m_updateThread;
    bool m_isDesroy = false;
};