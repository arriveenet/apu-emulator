#include "Tracker.h"
#include "AudioEngine.h"
#include "ControlPanel.h"

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

    // Initialize audio
    m_audioStream.setApu(&m_apu);
    m_apu.writeStatusRegister(0x04);
    m_audioStream.play();

    // Create a new song
    m_song = std::make_shared<Song>("New song");
    m_editorContext.setCurrentSong(m_song);

    // Initialize windows
    m_windows.push_back(new ControlPanel());

    return true;
}

void Tracker::update()
{
    m_song->update();
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
}

void Tracker::reset()
{
    m_apu.writeStatusRegister(0x00);
}
