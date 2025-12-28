#include "PatternEditor.h"
#include "EditorContext.h"
#include <imgui.h>

PatternEditor::PatternEditor()
{
}

PatternEditor::~PatternEditor()
{
}
void PatternEditor::draw(const EditorContext& context)
{
    ImGui::Begin("Pattern Editor");
    auto song = context.getCurrentSong();
    ImGui::End();
}
