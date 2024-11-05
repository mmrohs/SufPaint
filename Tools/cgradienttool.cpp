#include "cgradienttool.h"


CGradientTool::CGradientTool()
    : CTool(EnumTools::ToolGradient)
{
}

/*virtual*/ QString CGradientTool::GetToolName()
{
    return "Color Gradient";
}

/*virtual*/ QString CGradientTool::GetTooltip()
{
    return "Fill areas with a color gradient";
}

/*virtual*/ QIcon CGradientTool::GetToolIcon()
{
    QIcon icon("Icons/Gradient.png");
    icon.addFile("Icons/Gradient_Disabled.png", QSize(), QIcon::Mode::Disabled);
    return icon;
}

/*virtual*/ void CGradientTool::ProcessMousePressEvent(QMouseEvent* pEvent, CImageView* pView)
{

}
