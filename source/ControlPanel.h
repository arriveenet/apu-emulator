#include "IWindow.h"

class ControlPanel : public IWindow {
public:
    ControlPanel();
    ~ControlPanel();

    void draw(EditorContext& context) override;
};
