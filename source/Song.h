#pragma once
#include "Pattern.h"
#include <stdint.h>
#include <string>

class Song {
public:
    static constexpr int DEFAULT_SPEED = 6;
    static constexpr int DEFAULT_TEMPO = 150;

    explicit Song(std::string_view title);
    Song(std::string_view title, int speed, int tempo);

    void setTitle(std::string_view title) { m_title = title; }
    const std::string& getTitle() const { return m_title; }

    void setSpeed(int speed) { m_speed = speed; }
    int getSpeed() const { return m_speed; }

    void setTempo(int tempo) { m_tempo = tempo; }
    int getTempo() const { return m_tempo; }

    void setPattern(const Pattern& pattern) { m_pattern = pattern; }
    Pattern& getPattern() { return m_pattern; }

private:
    std::string m_title;
    int m_speed;
    int m_tempo;
    uint32_t m_tickCounter = 0;
    Pattern m_pattern;
};
