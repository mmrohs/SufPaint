#include "crectangleselectiontool.h"


CRectangleSelectionTool::CRectangleSelectionTool()
    : CTool(EnumTools::ToolRectSelect)
{
}

/*virtual*/ QString CRectangleSelectionTool::GetToolName()
{
    return "Rectangle Select";
}

/*virtual*/ QString CRectangleSelectionTool::GetTooltip()
{
    return "Select a rectangular area";
}

/*virtual*/ QIcon CRectangleSelectionTool::GetToolIcon()
{
    QIcon icon("Icons/RectSelection.png");
    icon.addFile("Icons/RectSelection_Disabled.png", QSize(), QIcon::Mode::Disabled);
    return icon;
}

/*virtual*/ void CRectangleSelectionTool::ProcessMousePressEvent(QPoint pos, QMouseEvent* pEvent)
{
    QImage* pImage = GetImage();
    if (pImage != NULL && pImage->rect().contains(pos))
    {

    }
}
