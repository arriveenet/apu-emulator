#pragma once

static constexpr int CHANNEL_DEFAULT_COUNT = 5;

class Channel {
public:
    enum ChannelType {
        Pulse1,
        Pulse2,
        Triangle,
        Noise,
        DPCM,
        Max
    };

    Channel() = default;
    virtual ~Channel() = default;
};