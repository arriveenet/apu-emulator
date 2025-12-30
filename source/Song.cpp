#include "Song.h"
#include "canon.h"
#include <stdio.h>

Song::Song(std::string_view title)
    : Song(title, DEFAULT_SPEED, DEFAULT_TEMPO)
{
    std::vector<Note> patternNotes;
    for (const auto& note : canon::PULSE1_TABLE) {
        auto len = note.length / 8;
        int oct = note.key >= 3 && note.key < 12 ? note.oct - 1 : note.oct;
        Note adjustedNote = {note.key, oct, len};
        patternNotes.push_back(adjustedNote);

        for (int i = 0; i < len - 1; i++) {
            patternNotes.push_back({NONE, 0, 1});
        }
    }
    m_pattern.setNote(patternNotes);
}

Song::Song(std::string_view title, int speed, int tempo)
    : m_title(title)
    , m_speed(speed)
    , m_tempo(tempo)
{
}
