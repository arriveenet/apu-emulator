#pragma once
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

    void keyCallback(int key, bool isPressed);

private:
    EditorContext m_editorContext;
    std::shared_ptr<Song> m_song;
    std::vector<IWindow*> m_windows;
};