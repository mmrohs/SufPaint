#include "cstatusbartoollabel.h"
#include "../Management/ctoolmanager.h"


CStatusBarToolLabel::CStatusBarToolLabel(QWidget* pParent)
    : QLabel("", pParent)
{
    Update();
}

void CStatusBarToolLabel::Update()
{
    CTool* pTool = CToolManager::GetToolManager()->GetActiveTool();
    if (pTool != NULL)
    {
        QString toolName = pTool->GetStatusText();
        setText(QString("  Current tool: %1").arg(toolName));
    }
}
