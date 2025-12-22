#include "EnvelopeUnit.h"

void EnvelopeUnit::clock()
{
    if (m_startFlag) {
        m_startFlag = false;
        m_decayLevelCounter = 15;
        m_divider = 0;
    }
    else {
        if (m_divider == 0) {
            m_divider = 15;
            if (m_decayLevelCounter > 0) {
                m_decayLevelCounter--;
            }
        }
        else {
            m_divider--;
        }
    }
}

void EnvelopeUnit::start()
{
    m_startFlag = true;
}

uint8_t EnvelopeUnit::getOutput()
{
    return 0;
}

void EnvelopeUnit::setConstantVolumeFlag(bool flag)
{
    m_constantVolumeFlag = flag;
}

void EnvelopeUnit::setDividerPeriod(uint8_t period)
{
    m_dividerPeriod = period;
}
