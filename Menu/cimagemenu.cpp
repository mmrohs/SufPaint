#include "cimagemenu.h"
#include "../cimagemanager.h"
#include "../cactionmanager.h"

CImageMenu::CImageMenu(const QString& title, QWidget* parent)
    : CMenuBase(title, parent), m_pImageManager(NULL)
{
    m_pImageManager = CImageManager::GetImageManager();

    AddActions();
    AddConnections();
}

void CImageMenu::AddActions()
{
    AddActionToMenu(ActionImageResize);
    AddActionToMenu(ActionImageResizeCanvas);
    addSeparator();
    AddActionToMenu(ActionImageRotate90C);
    AddActionToMenu(ActionImageRotate90CC);
    AddActionToMenu(ActionImageRotate180);
    addSeparator();
    AddActionToMenu(ActionImageMirrorHor);
    AddActionToMenu(ActionImageMirrorVer);
}

void CImageMenu::AddConnections()
{
    ConnectAction(ActionImageResize, &CImageMenu::Resize);
    ConnectAction(ActionImageResizeCanvas, &CImageMenu::ResizeCanvas);
    ConnectAction(ActionImageRotate90C, &CImageMenu::Rotate90C);
    ConnectAction(ActionImageRotate90CC, &CImageMenu::Rotate90CC);
    ConnectAction(ActionImageRotate180, &CImageMenu::Rotate180);
    ConnectAction(ActionImageMirrorHor, &CImageMenu::MirrorHor);
    ConnectAction(ActionImageMirrorVer, &CImageMenu::MirrorVer);
}

template<typename func>
void CImageMenu::ConnectAction(EnumActions e, func&& slot)
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

void CImageMenu::Resize()
{
    if (m_pImageManager != NULL)
    {
        m_pImageManager->Resize();
    }
}

void CImageMenu::ResizeCanvas()
{
    if (m_pImageManager != NULL)
    {
        m_pImageManager->ResizeCanvas();
    }
}

void CImageMenu::Rotate90C()
{
    if (m_pImageManager != NULL)
    {
        m_pImageManager->Rotate90C();
    }
}

void CImageMenu::Rotate90CC()
{
    if (m_pImageManager != NULL)
    {
        m_pImageManager->Rotate90CC();
    }
}

void CImageMenu::Rotate180()
{
    if (m_pImageManager != NULL)
    {
        m_pImageManager->Rotate180();
    }
}

void CImageMenu::MirrorHor()
{
    if (m_pImageManager != NULL)
    {
        m_pImageManager->MirrorHor();
    }
}

void CImageMenu::MirrorVer()
{
    if (m_pImageManager != NULL)
    {
        m_pImageManager->MirrorVer();
    }
}
