#pragma once
#include <AL/al.h>
#include <AL/alc.h>

class AudioEngine {
public:
    static bool init();
    static void terminate();

private:
    static ALCdevice* s_pALDevice;
    static ALCcontext* s_pALContext;
};