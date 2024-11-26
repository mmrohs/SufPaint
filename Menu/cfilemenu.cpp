#include "cfilemenu.h"
#include "../Management/cimagemanager.h"
#include "../Management/cactionmanager.h"

CFileMenu::CFileMenu(const QString& title, QWidget* pParent)
    : CMenuBase(title, pParent), m_pImageManager(NULL)
{
    m_pImageManager = CImageManager::GetImageManager();

    AddActions();
    AddConnections();
}

void CFileMenu::AddActions()
{
    AddActionToMenu(FileNew);
    AddActionToMenu(FileOpen);
    AddActionToMenu(FileClose);
    addSeparator();
    AddActionToMenu(FileSave);
    AddActionToMenu(FileSaveAs);
    addSeparator();
    AddActionToMenu(FileQuit);
}

void CFileMenu::AddConnections()
{
    ConnectAction(FileNew, &CFileMenu::NewImage);
    ConnectAction(FileOpen, &CFileMenu::OpenImage);
    ConnectAction(FileClose, &CFileMenu::CloseImage);
    ConnectAction(FileSave, &CFileMenu::SaveImage);
    ConnectAction(FileSaveAs, &CFileMenu::SaveAsImage);
    ConnectAction(FileQuit, &CFileMenu::Quit);
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
