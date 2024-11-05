#include "cpenciltool.h"


CPencilTool::CPencilTool()
    : CTool(EnumTools::ToolPencil)
{
}

/*virtual*/ QString CPencilTool::GetToolName()
{
    return "Pencil";
}

/*virtual*/ QString CPencilTool::GetTooltip()
{
    return "Draw with a pencil";
}

/*virtual*/ QIcon CPencilTool::GetToolIcon()
{
    QIcon icon("Icons/Pencil.png");
    icon.addFile("Icons/Pencil_Disabled.png", QSize(), QIcon::Mode::Disabled);
    return icon;
}

/*virtual*/ void CPencilTool::ProcessMousePressEvent(QMouseEvent* pEvent, CImageView* pView)
{

}
