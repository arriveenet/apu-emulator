#pragma once
#include "EditorContext.h"

class IWindow {
public:
    virtual ~IWindow() = default;

    virtual void draw(const EditorContext& context) = 0;
};