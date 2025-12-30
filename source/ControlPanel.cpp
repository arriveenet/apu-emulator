#include "ControlPanel.h"
#include "AudioEngine.h"
#include <imgui.h>

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

    if (ImGui::InputInt("Speed", &speed)) {
        song->setSpeed(speed);
    }
    if (ImGui::InputInt("Tempo", &tempo)) {

        song->setTempo(tempo);
    }

    ImGui::End();
}
