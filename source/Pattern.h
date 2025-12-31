#pragma once
#include "Channel.h"
#include "Note.h"
#include <vector>

class Pattern {
public:
    Pattern();
    ~Pattern();

    void init(int rows, int channels = CHANNEL_DEFAULT_COUNT);

    [[nodiscard]] int getRowCount() const;
    [[nodiscard]] int getChannelCount() const;

    Note& getNote(int row, int channel)
    {
        return m_data[row * m_channelCount + channel];
    }

    [[nodiscard]] const Note& getNote(int row, int channel) const
    {
        return m_data[row * m_channelCount + channel];
    }

private:
    int m_rowCount = 0;
    int m_channelCount = 0;
    std::vector<Note> m_data;
};