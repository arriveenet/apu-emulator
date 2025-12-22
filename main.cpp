#include "Apu.h"
#include "AudioEngine.h"
#include "AudioStream.h"
#include <stdio.h>
#include <chrono>

bool isRunning = true;

int main()
{
    if (!AudioEngine::init()) {
        return -1;
    }


    APU apu;

    AudioStream stream;
    stream.setApu(&apu);

    apu.writeStatusRegister(0x04);
    // Pulse 1
    apu.writeRegister(0x4000, 0b01000001); // Duty cycle 50%, envelope
    apu.writeRegister(0x4001, 0x00); // Sweep
    apu.writeRegister(0x4002, 0xFF); // Timer low
    apu.writeRegister(0x4003, 0x09); // Timer high, length counter

    stream.play();

    while (isRunning) {
        int ch = getchar();
        if (ch == 'q') {
            isRunning = false;
        }
    }

    AudioEngine::terminate();

    return 0;
}

