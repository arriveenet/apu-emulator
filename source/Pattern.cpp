#include "Pattern.h"
#include  <stdio.h>

Pattern::Pattern()
{
}

Pattern::~Pattern()
{
}

void Pattern::init(int rows, int channels)
{
    m_rowCount = rows;
    m_channelCount = channels;
    m_data.resize(rows * channels);
    m_data.assign(rows * channels, Note());
}

int Pattern::getRowCount() const
{
    return m_rowCount;
}

int Pattern::getChannelCount() const
{
    return m_channelCount;
}
