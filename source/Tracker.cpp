#include "Tracker.h"
#include "AudioEngine.h"


Tracker::Tracker()
{
}

Tracker::~Tracker()
{
    AudioEngine::terminate();
}

bool Tracker::init()
{
    if (!AudioEngine::init()) {
        return false;
    }

    m_audioStream.setApu(&m_apu);

    m_apu.writeStatusRegister(0x04);

    m_audioStream.play();

    m_currentScore = canonP0[0];

    return true;
}

void Tracker::update()
{
    if (m_frameCounter > m_currentScore.length) {
        m_frameCounter = 0;
        m_currentScore = canonP0[m_scoreIndex++];

        if (m_currentScore.key == REST) {
            return;
        }

        int oct = m_currentScore.key >= 3 && m_currentScore.key < 12 ? m_currentScore.oct - 1
                                                                     : m_currentScore.oct;
        float freq = score_octave[oct] * powf(2, m_currentScore.key / 12.f);
        uint16_t timer = static_cast<uint16_t>((1789773 / (8.0 * freq)) - 1.0);
        if (timer < 2)
            timer = 2;

        m_apu.writeRegister(0x4000, 0xff);          // Volume Envelope
        m_apu.writeRegister(0x4001, 0x00);          // Sweep
        m_apu.writeRegister(0x4002, timer & 0xFF); // Frequency low
        m_apu.writeRegister(0x4003, (timer >> 8) & 0x07); // Frequency high + trigger

        printf("Playing note: %s%d Freq: %.2f Hz\n", score_scale[m_currentScore.key],
               m_currentScore.oct, freq);
    }
    else {
        m_frameCounter++;
    }
}

void Tracker::draw()
{
}
