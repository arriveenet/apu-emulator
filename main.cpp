#include "Apu.h"
#include "AudioEngine.h"
#include "AudioStream.h"
#include <stdio.h>
#include <chrono>
#include <termios.h>
#include <unistd.h>

bool isRunning = true;

int main()
{
    if (!AudioEngine::init()) {
        return -1;
    }

    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);

    termios newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    APU apu;

    AudioStream stream;
    stream.setApu(&apu);

    apu.writeStatusRegister(0x04);

    apu.dump();

    stream.play();

    bool isFirst = false;

    while (isRunning) {
        char c;
        if(read(STDIN_FILENO, &c, 1) > 0) {
            if (c == 'q' || c == 0x2C) {
                isRunning = false;
            }

            if (!isFirst) {
                apu.writeRegister(0x4008, 0b11111111);
                isFirst = true;
            }

            // A4
            if (c == 'a') {
                apu.writeRegister(0x400A, 0x7E);
                apu.writeRegister(0x400B, 0x00);
            }
            
            // B4
            if (c == 's') {
                apu.writeRegister(0x400A, 0x70);
                apu.writeRegister(0x400B, 0x00);
            }

            // C5
            if (c == 'd') {
                apu.writeRegister(0x400A, 0x69);
                apu.writeRegister(0x400B, 0x00);
            }

            // D5
            if (c == 'f') {
                apu.writeRegister(0x400A, 0x5D);
                apu.writeRegister(0x400B, 0x00);
            }

            // E5
            if (c == 'g') {
                apu.writeRegister(0x400A, 0x54);
                apu.writeRegister(0x400B, 0x00);
            }

            // F5
            if (c == 'h') {
                apu.writeRegister(0x400A, 0x4F);
                apu.writeRegister(0x400B, 0x00);
            }

            // G5
            if (c == 'j') {
                apu.writeRegister(0x400A, 0x46);
                apu.writeRegister(0x400B, 0x00);
            }

            // A5
            if (c == 'k') {
                apu.writeRegister(0x400A, 0x3E);
                apu.writeRegister(0x400B, 0x00);
            }

            // B5
            if (c == 'l') {
                apu.writeRegister(0x400A, 0x36);
                apu.writeRegister(0x400B, 0x00);
            }

        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    AudioEngine::terminate();

    return 0;
}

