#pragma once
#include "apu/Apu.h"
#include "AudioStream.h"
#include "canon.h"

class Tracker {
public:
    Tracker();
    ~Tracker();

    bool init();

    void update();

    void draw();

private:
    AudioStream m_audioStream;
    Apu m_apu;
    uint32_t m_frameCounter = 0;
    SCORE m_currentScore;
    uint32_t m_scoreIndex = 0;
};