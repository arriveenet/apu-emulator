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

    apu.writeRegister(0x4008, 0xFF);
    apu.writeRegister(0x400A, 0xFF);
    apu.writeRegister(0x400B, 0xF8);

    apu.dump();

    stream.play();

    while (isRunning) {
        const int ch = getchar();
        if (ch == 'q') {
            isRunning = false;
        }
    }

    AudioEngine::terminate();

    return 0;
}

