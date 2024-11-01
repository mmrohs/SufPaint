#include "cstatusbartoollabel.h"
#include "../Management/ctoolmanager.h"


CStatusBarToolLabel::CStatusBarToolLabel(QWidget* pParent)
    : QLabel("", pParent)
{
    Update();
}

void CStatusBarToolLabel::Update()
{
    QString toolName = CToolManager::GetToolManager()->GetActiveToolName();
    setText(QString("  Current tool: %1").arg(toolName));
}
