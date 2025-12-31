#pragma once
#include <stdint.h>

enum Key : int8_t {
    NONE = -1,
    A,
    A_SHARP,
    B,
    C,
    C_SHARP,
    D,
    D_SHARP,
    E,
    F,
    F_SHARP,
    G,
    G_SHARP,
    REST,
    SCALE_MAX
};

static constexpr float NOTE_OCTAVE[] = {27.5, 55, 110, 220, 440, 880, 1760, 3520, 7040, 0};

static constexpr char NOTE_NAMES[][3] = {"A-", "A#", "B-",  "C-", "C#", "D-", "D#",
                                      "E-", "F-",  "F#", "G-", "G#", "=="};

struct Note {
    Key key = Key::NONE;
    int oct = 0;
    unsigned int length = 0;
    float decay = 0.0f;
    float freq = 0.0f;
};
