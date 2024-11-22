#include "cpenciltool.h"


CPencilTool::CPencilTool()
    : CTool(EnumTools::ToolPencil)
{
}

/*virtual*/ QIcon CPencilTool::GetToolIcon() const
{
    QIcon icon("Icons/Pencil.png");
    icon.addFile("Icons/Pencil_Disabled.png", QSize(), QIcon::Mode::Disabled);
    return icon;
}

/*virtual*/ QString CPencilTool::GetToolName() const
{
    return "Pencil";
}

/*virtual*/ QString CPencilTool::GetTooltip() const
{
    return "Draw with a pencil";
}

/*virtual*/ void CPencilTool::ProcessMouseLPressEvent(QMouseEvent* pEvent)
{

}
