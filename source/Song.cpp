#include "Song.h"
#include <stdio.h>

Song::Song(std::string_view title)
    : Song(title, DEFAULT_SPEED, DEFAULT_TEMPO)
{
}

Song::Song(std::string_view title, int speed, int tempo)
    : m_title(title)
    , m_speed(speed)
    , m_tempo(tempo)
{
}

void Song::update()
{
    m_tickCounter++;

    if ( m_tickCounter >= m_speed )
    {
        m_tickCounter = 0;
    }
}
