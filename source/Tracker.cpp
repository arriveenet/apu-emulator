#include "Tracker.h"
#include "AudioEngine.h"
#include "ControlPanel.h"
#include "PatternEditor.h"
#include <algorithm>
#include <GLFW/glfw3.h>

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

void Tracker::keyCallback(int key, bool isPressed)
{
    bool isChanged = false;
    Note note;
    note.key =Key::NONE;
    int octave = m_editorContext.getOctave();
    switch (key) {
    case GLFW_KEY_Z: note.key = Key::C; break;
    case GLFW_KEY_S: note.key = Key::C_SHARP; break;
    case GLFW_KEY_X: note.key = Key::D; break;
    case GLFW_KEY_D: note.key = Key::D_SHARP; break;
    case GLFW_KEY_C: note.key = Key::E; break;
    case GLFW_KEY_V: note.key = Key::F; break;
    case GLFW_KEY_G: note.key = Key::F_SHARP; break;
    case GLFW_KEY_B: note.key = Key::G; break;
    case GLFW_KEY_H: note.key = Key::G_SHARP; break;
    case GLFW_KEY_N: note.key = Key::A; octave++; break;
    case GLFW_KEY_J: note.key = Key::A_SHARP; octave++; break;
    case GLFW_KEY_M: note.key = Key::B; octave++; break;
    default: break;
    }
    note.oct = octave;

    if (isPressed && note.key != Key::NONE) {
        m_activeKeys.push_back(note);
    }
    else {
        const auto iter = std::remove(m_activeKeys.begin(),
            m_activeKeys.end(), note);
        m_activeKeys.erase(iter, m_activeKeys.end());
    }

    if (m_activeKeys.empty()) {
        AudioEngine::getInstance()->noteOff();
    }
    else {
        const Note lastNote = m_activeKeys.back();
        AudioEngine::getInstance()->noteOn(lastNote.key, lastNote.oct);
    }
}