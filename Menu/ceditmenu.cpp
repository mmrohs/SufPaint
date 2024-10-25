#include "ceditmenu.h"
#include "../cactionmanager.h"
#include "../cimagemanager.h"


CEditMenu::CEditMenu(const QString& title, QWidget* parent)
    : CMenuBase(title, parent), m_pImageManager(NULL)
{
    m_pImageManager = CImageManager::GetImageManager();

    AddActions();
    AddConnections();
}

void CEditMenu::AddActions()
{
    AddActionToMenu(ActionEditUndo);
    AddActionToMenu(ActionEditRedo);
    addSeparator();
    AddActionToMenu(ActionEditCopy);
    AddActionToMenu(ActionEditPaste);
    AddActionToMenu(ActionEditCut);
}

void CEditMenu::AddConnections()
{
    CMenuBase::ConnectAction(ActionEditUndo);
    CMenuBase::ConnectAction(ActionEditRedo);
    ConnectAction(ActionEditCopy, &CEditMenu::CopyImage);
    ConnectAction(ActionEditPaste, &CEditMenu::PasteImage);
    ConnectAction(ActionEditCut, &CEditMenu::CutImage);
}

template<typename func>
void CEditMenu::ConnectAction(EnumActions e, func&& slot)
{
    CActionManager* pActionManager = CActionManager::GetActionManager();
    if (pActionManager != NULL)
    {
        QAction* pAction = pActionManager->FindAction(e);
        if (pAction != NULL)
        {
            connect(pAction, &QAction::triggered, this, slot);
        }
    }
}

void CEditMenu::CopyImage()
{
    if (m_pImageManager != NULL)
    {
        m_pImageManager->CopyImage();
    }
}

void CEditMenu::PasteImage()
{
    if (m_pImageManager != NULL)
    {
        m_pImageManager->PasteImage();
    }
}

void CEditMenu::CutImage()
{
    if (m_pImageManager != NULL)
    {
        m_pImageManager->CutImage();
    }
}
