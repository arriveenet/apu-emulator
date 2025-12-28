#pragma once
#include "Note.h"
#include <vector>

class Pattern {
public:
    Pattern();

    Note& getNote(int row, int channel);

private:
    std::vector<Note> m_data;
};