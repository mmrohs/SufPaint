#include "ctoolmanager.h"
#include "../Tools/ccolorpickertool.h"
#include "../EnumFunctions.h"


/*static*/ CToolManager* CToolManager::m_pSingletonInstance = NULL;

CToolManager::CToolManager()
    : m_pTool(NULL)
{
    SetActiveTool(EnumTools::ToolNone);
}

/*static*/ CToolManager* CToolManager::GetToolManager()
{
    if (m_pSingletonInstance == NULL)
    {
        m_pSingletonInstance = new CToolManager();
    }
    return m_pSingletonInstance;
}

/* Returns an instance of the currently selected tool class
 * Beware: returns NULL if no tool is selected
*/
CTool* CToolManager::GetActiveTool()
{
    if (m_pTool == NULL)
    {
        CreateTool();
    }
    return m_pTool;
}

QString CToolManager::GetActiveToolName()
{
    CTool* pTool = GetActiveTool();
    if (pTool != NULL)
    {
        return pTool->GetToolName();
    }
    return "";
}

EnumTools CToolManager::GetActiveToolEnum() const
{
    return m_activeTool;
}

void CToolManager::SetActiveTool(EnumTools tool)
{
    bool bToolChange = m_activeTool != tool;
    m_activeTool = tool;
    if (bToolChange)
    {
        delete m_pTool;
        m_pTool = NULL;
        emit ToolChanged();
    }
}

bool CToolManager::IsActiveTool(EnumTools tool) const
{
    return m_activeTool == tool;
}

void CToolManager::CreateTool()
{
    assert(m_pTool == NULL);
    m_pTool = GetNewTool(m_activeTool);
}
