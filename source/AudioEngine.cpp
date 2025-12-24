#include "AudioEngine.h"
#include <stdio.h>
#include "Tracker.h"

ALCdevice* AudioEngine::s_pALDevice = nullptr;
ALCcontext* AudioEngine::s_pALContext = nullptr;

bool AudioEngine::init()
{
    bool result = false;
    do {
        s_pALDevice = alcOpenDevice(nullptr);

        if (s_pALDevice != nullptr) {
            s_pALContext = alcCreateContext(s_pALDevice, nullptr);
            alcMakeContextCurrent(s_pALContext);

            ALenum alError = alGetError();
            if (alError != AL_NO_ERROR) {
                break;
            }

            const char* vender = alGetString(AL_VENDOR);
            const char* version = alGetString(AL_VERSION);

            printf("OpenAL initialization successful. vender: %s, version: %s\n", vender,
                         version);

            result = true;
        }
        else {
            printf("OpenAL initialization failed. alcOpenDevice() failed.");
            break;
        }
    } while (false);

    return result;
}

void AudioEngine::terminate()
{
    if (s_pALContext != nullptr) {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(s_pALContext);
        s_pALContext = nullptr;
    }

    if (s_pALDevice != nullptr) {
        alcCloseDevice(s_pALDevice);
        s_pALDevice = nullptr;
    }
}
