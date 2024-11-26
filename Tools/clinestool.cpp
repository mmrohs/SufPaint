#include "clinestool.h"


CLinesTool::CLinesTool()
    : CTool(EnumTools::Line)
{
}

/*virtual*/ QIcon CLinesTool::GetToolIcon() const
{
    QIcon icon("Icons/LineTool.png");
    icon.addFile("Icons/LineTool_Disabled.png", QSize(), QIcon::Mode::Disabled);
    return icon;
}

/*virtual*/ QString CLinesTool::GetToolName() const
{
    return "Line Tool";
}

/*virtual*/ QString CLinesTool::GetTooltip() const
{
    return "Draw lines and splines";
}

/*virtual*/ void CLinesTool::ProcessMouseLPressEvent(QMouseEvent* pEvent)
{

}
