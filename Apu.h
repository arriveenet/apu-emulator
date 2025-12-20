#pragma once
#include "FrameSequencer.h"
#include "PulseChannel.h"
#include "TriangleChannel.h"
#include <stdint.h>

struct APU {
    enum StatusFlags {
        STATUS_PULSE1_ENABLED   = 1 << 0,
        STATUS_PULSE2_ENABLED   = 1 << 1,
        STATUS_TRIANGLE_ENABLED = 1 << 2,
        STATUS_NOISE_ENABLED    = 1 << 3,
        STATUS_DMC_ENABLED      = 1 << 4,

    };

    APU();

    // Clock the APU
    void clock();

    // Write registers
    void writeRegister(uint16_t address, uint8_t data);

    // Status register
    uint8_t readStatusRegister();
    void writeStatusRegister(uint8_t data);

    // Output sample
    float getOutput();

    void dump() const;

private:
    void clockFrameCounterQuarterFrame();
    void clockFrameCounterHalfFrame();

    uint8_t m_statusRegister = 0;
    uint32_t cycles = 0;
    uint32_t counter = 0;

    // Frame sequencer
    FrameSequencer m_frameSequencer;

    // Channels
    PulseChannel m_pulseChannel[2];
    TriangleChannel m_triangleChannel;

    friend FrameSequencer;
};
