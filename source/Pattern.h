#pragma once
#include "Note.h"
#include <vector>

class Pattern {
public:
    Pattern();
    ~Pattern();

    void inti();

    void setNote(const std::vector<Note>& data);
    void setNote(std::vector<Note>&& data);

    Note& getNote(int row, int channel);

    size_t size() const { return m_data.size(); }

private:
    std::vector<Note> m_data;
};