#include "clinestool.h"


CLinesTool::CLinesTool()
    : CTool(EnumTools::ToolLine)
{
}

/*virtual*/ QString CLinesTool::GetToolName()
{
    return "Line Tool";
}

/*virtual*/ QString CLinesTool::GetTooltip()
{
    return "Draw lines and splines";
}

/*virtual*/ QIcon CLinesTool::GetToolIcon()
{
    QIcon icon("Icons/LineTool.png");
    icon.addFile("Icons/LineTool_Disabled.png", QSize(), QIcon::Mode::Disabled);
    return icon;
}

/*virtual*/ void CLinesTool::ProcessMousePressEvent(QMouseEvent* pEvent, CImageView* pView)
{

}
