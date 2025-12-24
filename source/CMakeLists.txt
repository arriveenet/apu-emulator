cmake_minimum_required(VERSION 3.19)

project(apu_emulator CXX)

set(CMAKE_CXX_STANDARD 17)

set(TARGET apu_emulator)

set (HDRS
    apu/Apu.h
    apu/EnvelopeUnit.h
    apu/FrameSequencer.h
    apu/LengthCounter.h
    apu/SweepUnit.h
    apu/PulseChannel.h
    apu/TriangleChannel.h
    AudioEngine.h
    AudioStream.h
    Tracker.h
)

set (SRCS
    apu/Apu.cpp
    apu/EnvelopeUnit.cpp
    apu/LengthCounter.cpp
    apu/FrameSequencer.cpp
    apu/SweepUnit.cpp
    apu/PulseChannel.cpp
    apu/TriangleChannel.cpp
    AudioEngine.cpp
    AudioStream.cpp
    Tracker.cpp
    main.cpp
)

add_executable(${TARGET} ${HDRS} ${SRCS})

target_link_libraries(${TARGET} glad)
target_link_libraries(${TARGET} glfw)
target_link_libraries(${TARGET} OpenAL::OpenAL)
