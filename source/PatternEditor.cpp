#include "PatternEditor.h"
#include "AudioEngine.h"
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
    auto audioEngine = AudioEngine::getInstance();
    const int columnCount = pattern.getChannelCount() + 1;

    if (ImGui::BeginTable("table1", columnCount, m_tableFlags)) {
        // Setup columns
        ImGui::TableSetupColumn("Row", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoResize, 0.0f);
        ImGui::TableSetupColumn("Pulse 1");
        ImGui::TableSetupColumn("Pulse 2");
        ImGui::TableSetupColumn("Triangle");
        ImGui::TableSetupColumn("Noise");
        ImGui::TableHeadersRow();

        for (int row = 0; row < pattern.getRowCount(); row++) {
            ImGui::TableNextRow();

            if (audioEngine->getCurrentRow() == row) {
                ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, IM_COL32(255, 0, 0, 100));
                if (audioEngine->isPlaying()) {
                    ImGui::SetScrollHereY(0.5f);
                }
            }

            for (int column = 0; column < columnCount; column++) {
                ImGui::TableSetColumnIndex(column);

                if (column == 0) {
                    ImGui::Text("%d", row);
                    continue;
                }

                const Note& n = pattern.getNote(row, column - 1);
                switch (n.key) {
                case NONE:
                    ImGui::Text("--- --- ---");
                    break;
                case REST:
                    ImGui::Text("%s= === ===", NOTE_NAMES[n.key], n.oct, n.length);
                    break;
                default:
                    ImGui::Text("%s%d %d- ---", NOTE_NAMES[n.key], n.oct, n.length);
                    break;
                }

            }
        }
        ImGui::EndTable();
    }
    ImGui::End();
}
