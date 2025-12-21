#include "PulseChannel.h"

PulseChannel::PulseChannel()
{
}

void PulseChannel::clock()
{
}

void PulseChannel::clockFrameCounterQuarterFrame()
{

}

void PulseChannel::clockFrameCounterHalfFrame()
{
}

uint8_t PulseChannel::getOutput()
{
    return 0;
}

void PulseChannel::setRegister(uint8_t registerNumber, uint8_t data)
{
    // Duty cycle and envelope
    if (registerNumber == 0) {
        // Volume
        m_volume = data & 0x0F;

        // Envelope loop flag
        m_envelopeLoopFlag = (data & 0x10) != 0;

        // Constant volume flag
        m_constantVolumeFlag = (data & 0x20) != 0;

        // Duty cycle
        m_dutyCycle = (data & 0xC0) >> 6;
    }
    // Sweep unit
    else if (registerNumber  == 2) {
        
        
    }
    // Timer low
    else if (registerNumber == 3) {
        m_timer = (m_timer & 0x700) | data;
    }
    // Timer high and length counter load
    else if (registerNumber == 4) {
        m_timer = (m_timer & 0xFF) | ((data & 0x07) << 8);
    }
}