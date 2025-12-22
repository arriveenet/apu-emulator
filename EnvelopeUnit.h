#pragma once
#include <stdint.h>

struct EnvelopeUnit
{
    void clock();

    void start();

    uint8_t getOutput();

    void setConstantVolumeFlag(bool flag);

    void setDividerPeriod(uint8_t period);

private:
    bool m_startFlag = false;
    bool m_constantVolumeFlag = false;
    uint8_t m_divider = 0;
    uint8_t m_dividerPeriod = 0;
    uint8_t m_decayLevelCounter = 0;
};
