#include "cviewmenu.h"
#include "../Management/cactionmanager.h"
#include "../Management/cimageviewmanager.h"


CViewMenu::CViewMenu(const QString& title, QWidget* parent)
    : CMenuBase(title, parent)
{
    AddActions();
    AddConnections();
}

void CViewMenu::AddActions()
{
    AddActionToMenu(ViewZoomIn);
    AddActionToMenu(ViewZoomOut);
    AddActionToMenu(ViewOrigSize);
}

void CViewMenu::AddConnections()
{
    ConnectAction(ViewZoomIn, &CViewMenu::ZoomIn);
    ConnectAction(ViewZoomOut, &CViewMenu::ZoomOut);
    ConnectAction(ViewOrigSize, &CViewMenu::ResetZoom);
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
    CImageViewManager::GetImageViewManager()->ZoomIn();
}

void CViewMenu::ZoomOut()
{
    CImageViewManager::GetImageViewManager()->ZoomOut();
}

void CViewMenu::ResetZoom()
{
    CImageViewManager::GetImageViewManager()->ResetZoom();
}
