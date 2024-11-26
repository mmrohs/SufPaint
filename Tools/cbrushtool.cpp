#include "cbrushtool.h"


CBrushTool::CBrushTool()
    : CTool(EnumTools::Brush)
{
}

/*virtual*/ QIcon CBrushTool::GetToolIcon() const
{
    QIcon icon("Icons/Brush.png");
    icon.addFile("Icons/Brush_Disabled.png", QSize(), QIcon::Mode::Disabled);
    return icon;
}

/*virtual*/ QString CBrushTool::GetToolName() const
{
    return "Brush";
}

/*virtual*/ QString CBrushTool::GetTooltip() const
{
    return "Draw with a brush";
}

/*virtual*/ void CBrushTool::ProcessMouseLPressEvent(QMouseEvent* pEvent)
{

}
