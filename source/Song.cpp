#include "Song.h"
#include "canon.h"

Song::Song(std::string_view title)
    : Song(title, DEFAULT_SPEED, DEFAULT_TEMPO)
{
    m_pattern.init(9000);

    std::vector<Note> pulse1;
    for (const auto& note : canon::PULSE1_TABLE) {
        const unsigned int len = note.length / 8;
        const int oct = note.key >= 3 && note.key < 12 ? note.oct - 1 : note.oct;
        Note adjustedNote = {note.key, oct, len};
        pulse1.push_back(adjustedNote);

        for (int i = 0; i < len - 1; i++) {
            pulse1.push_back({NONE, 0, 1});
        }
    }

    std::vector<Note> pulse2;
    for (const auto& note : canon::PULSE2_TABLE) {
        const unsigned int len = note.length / 8;
        const int oct = note.key >= 3 && note.key < 12 ? note.oct - 1 : note.oct;
        Note adjustedNote = {note.key, oct, len};
        pulse2.push_back(adjustedNote);

        for (int i = 0; i < len - 1; i++) {
            pulse2.push_back({NONE, 0, 1});
        }
    }

    std::vector<Note> triangle;
    for (const auto& note : canon::TRIANGLE_TABLE) {
        const unsigned int len = note.length / 8;
        int oct = note.key >= 3 && note.key < 12 ? note.oct - 1 : note.oct;
        Note adjustedNote = {note.key, oct+=2, len};
        triangle.push_back(adjustedNote);

        for (int i = 0; i < len - 1; i++) {
            triangle.push_back({NONE, 0, 1});
        }
    }

    for (int i = 0; i < pulse1.size(); i++) {
        m_pattern.getNote(i, Channel::Pulse1) = pulse1[i];
    }
    for (int i = 0; i < pulse2.size(); i++) {
        m_pattern.getNote(i, Channel::Pulse2) = pulse2[i];
    }
    for (int i = 0; i < triangle.size(); i++) {
        m_pattern.getNote(i, Channel::Triangle) = triangle[i];
    }
}

Song::Song(std::string_view title, int speed, int tempo)
    : m_title(title)
    , m_speed(speed)
    , m_tempo(tempo)
{
}
