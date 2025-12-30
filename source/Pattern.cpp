#include "Pattern.h"
#include <algorithm>

Pattern::Pattern()
{
}

void Pattern::setNote(const std::vector<Note>& data)
{
    m_data = data;
}

void Pattern::setNote(std::vector<Note>&& data)
{
    m_data = std::move(data);
}

Note& Pattern::getNote(int row, int channel)
{
    return m_data[row];
}
