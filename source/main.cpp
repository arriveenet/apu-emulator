#include "AudioEngine.h"
#include "AudioStream.h"
#include "apu/Apu.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <chrono>

Apu g_apu;

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

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
    gladLoadGL();
    glfwSetKeyCallback(window, keyCallback);

    AudioStream stream;
    stream.setApu(&g_apu);

    g_apu.writeStatusRegister(0x04);

    // Pulse 1
    g_apu.writeRegister(0x4000, 0b10111111); // Duty cycle 50%, envelope
    g_apu.writeRegister(0x4001, 0x00); // Sweep
    g_apu.writeRegister(0x4002, 0xFF); // Timer low
    g_apu.writeRegister(0x4003, 0x09); // Timer high, length counter

    // Triangle
    g_apu.writeRegister(0x4008, 0xFF);
    g_apu.writeRegister(0x400A, 0xFF);
    g_apu.writeRegister(0x400B, 0xF8);

    stream.play();

    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
     }

    AudioEngine::terminate();
    glfwTerminate();

    return 0;
}

