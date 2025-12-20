cmake_minimum_required(VERSION 3.19)

project(apu_emulator CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(third-party/openal-soft)

set(TARGET apu_emulator)

set (HDRS
    Apu.h
    AudioEngine.h
    AudioStream.h
    FrameSequencer.h
    PulseChannel.h
    TriangleChannel.h
)

set (SRCS
    Apu.cpp
    AudioEngine.cpp
    AudioStream.cpp
    FrameSequencer.cpp
    PulseChannel.cpp
    TriangleChannel.cpp
    main.cpp
)

add_executable(${TARGET} ${HDRS} ${SRCS})

target_link_libraries(${TARGET} OpenAL::OpenAL)
