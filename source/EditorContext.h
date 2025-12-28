#pragma once
#include "Song.h"
#include <memory>

class EditorContext {
public:
    EditorContext();
    ~EditorContext();

    void init();

    void setCurrentSong(const std::shared_ptr<Song>& song);
    std::shared_ptr<Song> getCurrentSong() const;

private:
    std::shared_ptr<Song> m_currentSong;
};