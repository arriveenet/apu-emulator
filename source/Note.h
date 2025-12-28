#pragma once
#include <stdint.h>

enum Key : uint8_t {
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

static constexpr char NOTE_NAMES[][3] = {"A", "A#", "B",  "C", "C#", "D", "D#",
                                      "E", "F",  "F#", "G", "G#", "*"};

struct Note {
    Key key;
    int oct;
    unsigned int length;
    float decay;
    float freq;
};
