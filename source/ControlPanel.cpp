#include "ControlPanel.h"
#include <imgui.h>

ControlPanel::ControlPanel()
{
}

ControlPanel::~ControlPanel()
{
}

void ControlPanel::draw(const EditorContext& context)
{
    auto song = context.getCurrentSong();
    int speed = song->getSpeed();
    int tempo = song->getTempo();

    ImGui::Begin("Control Panel");
    ImGui::InputInt("Speed", &speed);
    ImGui::InputInt("Tempo", &tempo);
    ImGui::End();

    song->setSpeed(speed);
    song->setTempo(tempo);
}
