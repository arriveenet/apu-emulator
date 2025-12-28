#pragma once
#include "IWindow.h"

class PatternEditor : public IWindow {
public:
    PatternEditor();
    ~PatternEditor();
    void draw(const EditorContext& context) override;
};
