#include "cimagemenu.h"
#include "../Management/cimagemanager.h"
#include "../Management/cactionmanager.h"

CImageMenu::CImageMenu(const QString& title, QWidget* parent)
    : CMenuBase(title, parent), m_pImageManager(NULL)
{
    m_pImageManager = CImageManager::GetImageManager();

    AddActions();
    AddConnections();
}

void CImageMenu::AddActions()
{
    AddActionToMenu(ImageResize);
    AddActionToMenu(ImageResizeCanvas);
    AddActionToMenu(ImageCropSelection);
    addSeparator();
    AddActionToMenu(ImageRotate90C);
    AddActionToMenu(ImageRotate90CC);
    AddActionToMenu(ImageRotate180);
    addSeparator();
    AddActionToMenu(ImageMirrorHor);
    AddActionToMenu(ImageMirrorVer);
}

void CImageMenu::AddConnections()
{
    ConnectAction(ImageResize, &CImageMenu::Resize);
    ConnectAction(ImageResizeCanvas, &CImageMenu::ResizeCanvas);
    ConnectAction(ImageCropSelection, &CImageMenu::CropImage);
    ConnectAction(ImageRotate90C, &CImageMenu::Rotate90C);
    ConnectAction(ImageRotate90CC, &CImageMenu::Rotate90CC);
    ConnectAction(ImageRotate180, &CImageMenu::Rotate180);
    ConnectAction(ImageMirrorHor, &CImageMenu::MirrorHor);
    ConnectAction(ImageMirrorVer, &CImageMenu::MirrorVer);
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

void CImageMenu::CropImage()
{
    if (m_pImageManager != NULL)
    {
        m_pImageManager->CropImage();
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
