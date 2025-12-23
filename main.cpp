#include "Apu.h"
#include "AudioEngine.h"
#include "AudioStream.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <chrono>

bool isRunning = true;

int main()
{
    GLFWwindow* window = nullptr;
    if (!glfwInit()) {
        return -1;
    }

    if (!AudioEngine::init()) {
        return -1;
    }

     window = glfwCreateWindow(640, 480, "APU Enulator", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    Apu apu;
    AudioStream stream;
    stream.setApu(&apu);

    apu.writeStatusRegister(0x04);
    // Pulse 1
    apu.writeRegister(0x4000, 0b10111111); // Duty cycle 50%, envelope
    apu.writeRegister(0x4001, 0x00); // Sweep
    apu.writeRegister(0x4002, 0xFF); // Timer low
    apu.writeRegister(0x4003, 0x09); // Timer high, length counter

    // Triangle
    apu.writeRegister(0x4008, 0xFF);
    apu.writeRegister(0x400A, 0xFF);
    apu.writeRegister(0x400B, 0xF8);

    stream.play();

    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        //glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
     }

    AudioEngine::terminate();
    glfwTerminate();

    return 0;
}

