#include "Tracker.h"
#include "AudioEngine.h"
#include "ControlPanel.h"
#include "PatternEditor.h"
#include <imgui.h>

Tracker::Tracker()
{
}

Tracker::~Tracker()
{
    for (const auto& window : m_windows) {
        delete window;
    }
    AudioEngine::terminate();
}

bool Tracker::init()
{
    if (!AudioEngine::init()) {
        return false;
    }

    // Create a new song
    m_song = std::make_shared<Song>("New song");
    m_editorContext.setCurrentSong(m_song);

    // Initialize windows
    m_windows.push_back(new ControlPanel());
    m_windows.push_back(new PatternEditor());

    return true;
}

void Tracker::update()
{
    AudioEngine::getInstance()->update();
}

void Tracker::draw()
{
    for (const auto& window : m_windows) {
        window->draw(m_editorContext);
    }
}

void Tracker::play()
{
}

void Tracker::stop()
{
    AudioEngine::getInstance()->stop();
}

void Tracker::reset()
{
    AudioEngine::getInstance()->reset();
}
