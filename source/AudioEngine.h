#pragma once
#include "apu/Apu.h"
#include "AudioStream.h"
#include "Song.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <memory>

class AudioEngine {
public:
    static AudioEngine* getInstance();

    static bool init();
    static void terminate();

    // Delete copy constructor and assignment operator
    AudioEngine(const AudioEngine&) = delete;
    AudioEngine& operator=(const AudioEngine&) = delete;

    void play(std::shared_ptr<Song> song);

    void stop();

    void reset();

    void update();

    int getCurrentRow() const { return m_currentRow; }
    unsigned int getTickCounter() const { return m_tickCounter; }

    bool isPlaying() const { return m_isPlaying; }

protected:
    void processRow(int row, int channel);

private:
    AudioEngine();
    ~AudioEngine();

    static AudioEngine s_instance;
    static ALCdevice* s_pALDevice;
    static ALCcontext* s_pALContext;
    static Apu s_apu;
    static AudioStream s_audioStream;

    bool m_isPlaying = false;
    int m_currentRow = 0;
    unsigned int m_tickCounter = 0;
    std::shared_ptr<Song> m_currentSong;
};