cmake_minimum_required(VERSION 3.19)

project(apu_emulator CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(third-party/glad)
add_subdirectory(third-party/glfw)
add_subdirectory(third-party/openal-soft)
add_subdirectory(third-party/imgui/apu-emu)

add_subdirectory(source)
