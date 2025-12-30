#pragma once
#include "IWindow.h"
#include <imgui.h>

class PatternEditor : public IWindow {
public:
    PatternEditor();
    ~PatternEditor();
    void draw(EditorContext& context) override;

private:
    ImGuiTableFlags m_tableFlags;
};
