#include "cselectionmanager.h"


/*static*/ CSelectionManager* CSelectionManager::m_pSingletonInstance = NULL;

CSelectionManager::CSelectionManager()
    : m_pSelection(NULL)
{
}

/*static*/ CSelectionManager* CSelectionManager::GetSelectionManager()
{
    if (m_pSingletonInstance == NULL)
    {
        m_pSingletonInstance = new CSelectionManager();
    }
    return m_pSingletonInstance;
}

bool CSelectionManager::HasSelection() const
{
    return m_pSelection != NULL && m_pSelection->IsValid();
}

CSelection* CSelectionManager::GetSelection()
{
    if (HasSelection())
    {
        return m_pSelection;
    }
    return NULL;
}

void CSelectionManager::SetSelection(CSelection* pSelection)
{
    if (m_pSelection != pSelection)
    {
        delete m_pSelection;
    }
    m_pSelection = pSelection;
    emit SelectionChanged();
}

void CSelectionManager::ClearSelection()
{
    if (m_pSelection != NULL)
    {
        delete m_pSelection;
        m_pSelection = NULL;
    }
    emit SelectionChanged();
}

void CSelectionManager::ImagePropertiesChanged()
{
    ClearSelection();
}
