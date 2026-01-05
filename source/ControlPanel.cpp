#include "ControlPanel.h"
#include "AudioEngine.h"
#include  "AudioStream.h"
#include <imgui.h>
#include <math.h>

ControlPanel::ControlPanel()
{
}

ControlPanel::~ControlPanel()
{
}

void ControlPanel::draw(EditorContext& context)
{
    auto song = context.getCurrentSong();
    int speed = song->getSpeed();
    int tempo = song->getTempo();

    ImGui::Begin("Control Panel");
    if (ImGui::Button("Play")) {
        AudioEngine::getInstance()->play(song);
    }
    ImGui::SameLine();
    if (ImGui::Button("Stop")) {
        AudioEngine::getInstance()->stop();
    }

    int selectedOct = context.getOctave();
    const char* octItems[] = { "0", "1", "2", "3", "4", "5", "6", "7" };
    if (ImGui::Combo("Octave", &selectedOct, octItems, IM_ARRAYSIZE(octItems))) {
        context.setOctave(selectedOct);
    }

    if (ImGui::InputInt("Speed", &speed)) {
        song->setSpeed(speed);
    }
    if (ImGui::InputInt("Tempo", &tempo)) {

        song->setTempo(tempo);
    }

    ImGui::End();
}
