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

    void setOctave(int oct) { m_octave = oct; }
    int getOctave() const { return m_octave; }

private:
    std::shared_ptr<Song> m_currentSong;
    int m_octave = 4;
};