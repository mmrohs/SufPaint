#include "ctoolmanager.h"


/*static*/ CToolManager* CToolManager::m_pSingletonInstance = NULL;

/*static*/ CToolManager* CToolManager::GetToolManager()
{
    if (m_pSingletonInstance == NULL)
    {
        m_pSingletonInstance = new CToolManager();
    }
    return m_pSingletonInstance;
}

CToolManager::CToolManager()
{
    SetActiveTool(EnumTools::ToolNone);
}

void CToolManager::SetActiveTool(EnumTools tool)
{
    bool bToolChange = m_activeTool != tool;
    m_activeTool = tool;
    if (bToolChange)
        emit ToolChanged();
}

EnumTools CToolManager::GetActiveTool() const
{
    return m_activeTool;
}

bool CToolManager::IsActiveTool(EnumTools tool) const
{
    return m_activeTool == tool;
}
