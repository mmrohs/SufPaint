#include "ceditmenu.h"
#include "../Management/cactionmanager.h"
#include "../Management/cimagemanager.h"


CEditMenu::CEditMenu(const QString& title, QWidget* parent)
    : CMenuBase(title, parent), m_pImageManager(NULL)
{
    m_pImageManager = CImageManager::GetImageManager();

    AddActions();
    AddConnections();
}

void CEditMenu::AddActions()
{
    AddActionToMenu(EditUndo);
    AddActionToMenu(EditRedo);
    addSeparator();
    AddActionToMenu(EditCopy);
    AddActionToMenu(EditPaste);
    AddActionToMenu(EditCut);
}

void CEditMenu::AddConnections()
{
    CMenuBase::ConnectAction(EditUndo);
    CMenuBase::ConnectAction(EditRedo);
    ConnectAction(EditCopy, &CEditMenu::CopyImage);
    ConnectAction(EditPaste, &CEditMenu::PasteImage);
    ConnectAction(EditCut, &CEditMenu::CutImage);
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
