#include "Pattern.h"

Pattern::Pattern()
{
}

Note& Pattern::getNote(int row, int channel)
{
    Note& note = m_data[row * 16 + channel];
    return note;
}
