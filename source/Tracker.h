#pragma once
#include "apu/Apu.h"
#include "AudioStream.h"
#include "Song.h"
#include "canon.h"
#include "IWindow.h"
#include <vector>
#include <memory>

class Tracker {
public:
    Tracker();
    ~Tracker();

    bool init();

    void update();

    void draw();

    void play();

    void stop();

    void reset();

private:
    AudioStream m_audioStream;
    Apu m_apu;
    std::shared_ptr<Song> m_song;
    EditorContext m_editorContext;
    std::vector<IWindow*> m_windows;
};