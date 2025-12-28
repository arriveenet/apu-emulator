#include "EditorContext.h"

EditorContext::EditorContext()
{
}

EditorContext::~EditorContext()
{
}

void EditorContext::setCurrentSong(const std::shared_ptr<Song>& song)
{
    m_currentSong = song;
}

std::shared_ptr<Song> EditorContext::getCurrentSong() const
{
    return m_currentSong;
}
