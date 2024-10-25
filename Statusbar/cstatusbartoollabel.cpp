#include "cstatusbartoollabel.h"
#include "../EnumFunctions.h"
#include "../Management/ctoolmanager.h"


CStatusBarToolLabel::CStatusBarToolLabel(QWidget* pParent)
    : QLabel("", pParent)
{
    SetTool(EnumTools::ToolNone);
    UpdateText();
}

void CStatusBarToolLabel::Update()
{
    CToolManager* pToolManager = CToolManager::GetToolManager();
    if (pToolManager != NULL)
    {
        SetTool(pToolManager->GetActiveTool());
    }
}

void CStatusBarToolLabel::SetTool(EnumTools tool)
{
    bool bUpdate = m_tool != tool;
    m_tool = tool;
    if (bUpdate)
        UpdateText();
}

void CStatusBarToolLabel::UpdateText()
{
    QString toolName = GetToolName(m_tool);
    setText(QString("  Current tool: %1").arg(toolName));
}
