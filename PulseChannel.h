#pragma once
#include <stdint.h>

struct PulseChannel {
    PulseChannel();

    void clock();

    void clockFrameCounterQuarterFrame();
    void clockFrameCounterHalfFrame();

    uint8_t getOutput();

    void setRegister(uint8_t registerNumber, uint8_t data);

private:
    uint16_t m_frequency = 0;
    uint8_t m_lengthCounter = 0;

    uint16_t m_timer = 0;
    uint16_t m_timerCounter = 0;
    uint8_t m_dutyCycle = 0;
    uint8_t m_sequenceStep = 0;
    bool m_envelopeLoopFlag = false;
    bool m_constantVolumeFlag = false;
    uint8_t m_volume
};
