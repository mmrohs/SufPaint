#include "cviewmenu.h"
#include "../cimagemanager.h"
#include "../cactionmanager.h"

CViewMenu::CViewMenu(const QString& title, QWidget* parent)
    : CMenuBase(title, parent), m_pImageManager(NULL)
{
    m_pImageManager = CImageManager::GetImageManager();

    AddActions();
    AddConnections();
}

void CViewMenu::AddActions()
{
    AddActionToMenu(ActionViewZoomIn);
    AddActionToMenu(ActionViewZoomOut);
    AddActionToMenu(ActionViewOrigSize);
}

void CViewMenu::AddConnections()
{
    ConnectAction(ActionViewZoomIn, &CViewMenu::ZoomIn);
    ConnectAction(ActionViewZoomOut, &CViewMenu::ZoomOut);
    ConnectAction(ActionViewOrigSize, &CViewMenu::ResetZoom);
}

template<typename func>
void CViewMenu::ConnectAction(EnumActions e, func&& slot)
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

void CViewMenu::ZoomIn()
{
    if (m_pImageManager != NULL)
    {
        m_pImageManager->ZoomIn();
    }
}

void CViewMenu::ZoomOut()
{
    if (m_pImageManager != NULL)
    {
        m_pImageManager->ZoomOut();
    }
}

void CViewMenu::ResetZoom()
{
    if (m_pImageManager != NULL)
    {
        m_pImageManager->ResetZoom();
    }
}
