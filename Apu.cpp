#include "Apu.h"

APU::APU()
    : m_frameSequencer(*this)
{
}

void APU::clock()
{
    // Clock Frame Sequencer
    m_frameSequencer.clock();

    // Clock Channels
    m_triangleChannel.clock();
}

void APU::writeRegister(uint16_t address, uint8_t data)
{
    // Pulse registers
    if (address < 0x4008) {
    }
    // Triangle register
    else if (address < 0x400C) {
        m_triangleChannel.setRegister(address & 0x3, data);
    }
}

uint8_t APU::readStatusRegister()
{
    return 0;
}

void APU::writeStatusRegister(uint8_t data)
{
    m_triangleChannel.setLengthCounterEnabled(data & 0x04);
}

void APU::clockFrameCounterQuarterFrame()
{
    m_triangleChannel.clockFrameCounterQuarterFrame();
}

void APU::clockFrameCounterHalfFrame()
{
    m_triangleChannel.clockFrameCounterHalfFrame();
}

float APU::getOutput()
{
    uint8_t triangle = m_triangleChannel.getOutput();
    float out = (triangle / 15.0f) * 2.0f - 1.0f;
    return out;
}

void APU::dump() const
{
    m_triangleChannel.dump();
}
