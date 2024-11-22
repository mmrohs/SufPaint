#include "cgradienttool.h"


CGradientTool::CGradientTool()
    : CTool(EnumTools::ToolGradient)
{
}

/*virtual*/ QIcon CGradientTool::GetToolIcon() const
{
    QIcon icon("Icons/Gradient.png");
    icon.addFile("Icons/Gradient_Disabled.png", QSize(), QIcon::Mode::Disabled);
    return icon;
}

/*virtual*/ QString CGradientTool::GetToolName() const
{
    return "Color Gradient";
}

/*virtual*/ QString CGradientTool::GetTooltip() const
{
    return "Fill areas with a color gradient";
}

/*virtual*/ void CGradientTool::ProcessMouseLPressEvent(QMouseEvent* pEvent)
{

}
