#include "cselectionmanager.h"


/*static*/ CSelectionManager* CSelectionManager::m_pSingletonInstance = NULL;

CSelectionManager::CSelectionManager()
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
    return m_selection.IsValid();
}

const CSelection& CSelectionManager::GetSelection()
{
    return m_selection;
}

void CSelectionManager::SetSelection(const CSelection& selection)
{
    m_selection = selection;
    emit SelectionChanged();
}

void CSelectionManager::ResizeSelection(QRect rect)
{
    m_selection.Resize(rect);
    emit SelectionChanged();
}

void CSelectionManager::ClearSelection()
{
    m_selection.Clear();
    emit SelectionChanged();
}
