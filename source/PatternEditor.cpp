#include "PatternEditor.h"
#include "EditorContext.h"

PatternEditor::PatternEditor()
{
    m_tableFlags = ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_BordersV |
                   ImGuiTableFlags_BordersOuterV | ImGuiTableFlags_BordersInnerV;
}

PatternEditor::~PatternEditor()
{
}

void PatternEditor::draw(EditorContext& context)
{
    ImGui::Begin("Pattern Editor");
    auto song = context.getCurrentSong();
    auto& pattern = song->getPattern();

    if (ImGui::BeginTable("table1", 5, m_tableFlags)) {
        // Setup columns
        ImGui::TableSetupColumn("Row");
        ImGui::TableSetupColumn("Pulse 1");
        ImGui::TableSetupColumn("Pulse 2");
        ImGui::TableSetupColumn("Triangle");
        ImGui::TableSetupColumn("Noise");
        ImGui::TableHeadersRow();

        for (size_t row = 0; row < pattern.size(); row++) {
            ImGui::TableNextRow();
            for (size_t column = 0; column < 5; column++) {
                ImGui::TableSetColumnIndex(column);

                if (column == 0) {
                    ImGui::Text("%02X", row);
                    continue;
                }
                else if (column == 1) {
                    Note n = pattern.getNote(row, 0);
                    if (n.key == NONE) {
                        ImGui::Text("--- --- ---");
                    }
                    else if (n.key == REST) {
                        ImGui::Text("%s%d %d- ---", NOTE_NAMES[n.key], n.oct, n.length);
                    }
                    else {
                        ImGui::Text("%s%d %d- ---", NOTE_NAMES[n.key], n.oct, n.length);
                    }
                }
                else {
                    ImGui::Text("--- --- ---");
                }
            }
        }
        ImGui::EndTable();
    }
    ImGui::End();
}
