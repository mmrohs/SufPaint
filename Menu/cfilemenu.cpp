#include "cfilemenu.h"
#include "../cimagemanager.h"
#include "../cactionmanager.h"

CFileMenu::CFileMenu(const QString& title, QWidget* pParent)
    : CMenuBase(title, pParent), m_pImageManager(NULL)
{
    m_pImageManager = CImageManager::GetImageManager();

    AddActions();
    AddConnections();
}

void CFileMenu::AddActions()
{
    AddActionToMenu(ActionFileNew);
    AddActionToMenu(ActionFileOpen);
    AddActionToMenu(ActionFileClose);
    addSeparator();
    AddActionToMenu(ActionFileSave);
    AddActionToMenu(ActionFileSaveAs);
    addSeparator();
    AddActionToMenu(ActionFileQuit);
}

void CFileMenu::AddConnections()
{
    ConnectAction(ActionFileNew, &CFileMenu::NewImage);
    ConnectAction(ActionFileOpen, &CFileMenu::OpenImage);
    ConnectAction(ActionFileClose, &CFileMenu::CloseImage);
    ConnectAction(ActionFileSave, &CFileMenu::SaveImage);
    ConnectAction(ActionFileSaveAs, &CFileMenu::SaveAsImage);
    ConnectAction(ActionFileQuit, &CFileMenu::Quit);
}

template<typename func>
void CFileMenu::ConnectAction(EnumActions e, func&& slot)
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

void CFileMenu::NewImage()
{
    if (m_pImageManager != NULL)
    {
        m_pImageManager->NewImage();
    }
}

void CFileMenu::OpenImage()
{
    if (m_pImageManager != NULL)
    {
        m_pImageManager->OpenImage();
    }
}

void CFileMenu::CloseImage()
{
    if (m_pImageManager != NULL)
    {
        m_pImageManager->CloseImage();
    }
}

void CFileMenu::SaveImage()
{
    if (m_pImageManager != NULL)
    {
        m_pImageManager->SaveImage();
    }
}

void CFileMenu::SaveAsImage()
{
    if (m_pImageManager != NULL)
    {
        m_pImageManager->SaveAsImage();
    }
}

void CFileMenu::Quit()
{
    exit(EXIT_SUCCESS);
}
