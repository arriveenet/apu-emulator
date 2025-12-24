#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <chrono>
#include "Tracker.h"


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

     window = glfwCreateWindow(640, 480, "APU Enulator", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSetKeyCallback(window, keyCallback);

    Tracker tracker;
    if (!tracker.init()) {
        printf("Failed to initialize Tracker.\n");
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        tracker.update();

        tracker.draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
     }

    glfwTerminate();

    return 0;
}

