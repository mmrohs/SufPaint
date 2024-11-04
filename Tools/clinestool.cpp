#include "cbrushtool.h"


CBrushTool::CBrushTool()
    : CTool(EnumTools::ToolBrush)
{
}

/*virtual*/ QString CBrushTool::GetToolName()
{
    return "Brush";
}

/*virtual*/ QString CBrushTool::GetTooltip()
{
    return "Draw with a brush";
}

/*virtual*/ QIcon CBrushTool::GetToolIcon()
{
    QIcon icon("Icons/Brush.png");
    icon.addFile("Icons/Brush_Disabled.png", QSize(), QIcon::Mode::Disabled);
    return icon;
}

/*virtual*/ void CBrushTool::ProcessMousePressEvent(QPoint pos, QMouseEvent* pEvent)
{
    QImage* pImage = GetImage();
    if (pImage != NULL && pImage->rect().contains(pos))
    {
        // to do
    }
}
