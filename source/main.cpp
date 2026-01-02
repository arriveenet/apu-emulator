#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <stdio.h>
#include <chrono>
#include "Tracker.h"

static constexpr double MS_PER_UPDATE = 1.0 / 60.0;

Tracker g_tracker;

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    const bool isPressed = (action == GLFW_PRESS);
    if (key == GLFW_KEY_ESCAPE && isPressed) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    g_tracker.keyCallback(key, isPressed);
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

    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSetKeyCallback(window, keyCallback);

     // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);

    ImGui_ImplOpenGL3_Init(glsl_version);

    if (!g_tracker.init()) {
        printf("Failed to initialize Tracker.\n");
        return -1;
    }

    double accumlator = 0.0;
    auto currentTime = std::chrono::steady_clock::now();

    while (!glfwWindowShouldClose(window)) {
        auto nowTime = std::chrono::steady_clock::now();
        auto deltaTime =
            std::chrono::duration_cast<std::chrono::microseconds>(nowTime - currentTime).count() /
            1000000.0;
        deltaTime = std::min(deltaTime, 0.25);
        currentTime = nowTime;

        accumlator += deltaTime;

        while (accumlator >= MS_PER_UPDATE) {
            // Update tracker state
            g_tracker.update();
            accumlator -= MS_PER_UPDATE;
        }

        /* Poll for and process events */
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Draw
        g_tracker.draw();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
     }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

