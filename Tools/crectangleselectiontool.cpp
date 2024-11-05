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

/*virtual*/ void CRectangleSelectionTool::ProcessMousePressEvent(QMouseEvent* pEvent, CImageView* pView)
{

}

/*virtual*/ void CRectangleSelectionTool::ProcessMouseReleaseEvent(QMouseEvent* pEvent, CImageView* pView)
{

}

/*virtual*/ void CRectangleSelectionTool::ProcessMouseMoveEvent(QMouseEvent* pEvent, CImageView* pView)
{

}
