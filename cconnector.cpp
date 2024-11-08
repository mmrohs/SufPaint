#include "cconnector.h"
#include <QClipboard>
#include "mainwindow.h"
#include "Widgets/cimageview.h"
#include "Widgets/ctoolwidget.h"
#include "Management/cactionmanager.h"
#include "Management/cimagemanager.h"
#include "Management/ctoolmanager.h"


CConnector::CConnector(MainWindow* pMainWindow)
    : m_pMainWindow(pMainWindow)
{
}

void CConnector::ConnectAll()
{
    CImageView* pImageView = m_pMainWindow->m_pImageView;
    CToolWidget* pToolWidget = m_pMainWindow->m_pToolWidget;
    CStatusBar* pStatusBar = m_pMainWindow->m_pStatusBar;

    connect(pImageView, &CImageView::ViewChanged, pStatusBar, &CStatusBar::ZoomUpdate);

    CImageManager* pImageManager = CImageManager::GetImageManager();
    connect(pImageManager, &CImageManager::ImageUpdate, pStatusBar, &CStatusBar::ImageUpdate);
    connect(pImageManager, &CImageManager::ImageUpdate, pToolWidget, &CToolWidget::ImageChanged);
    connect(pImageManager, &CImageManager::ImageUpdate, pImageView, &CImageView::ImageChanged);

    CActionManager* pActionManager = CActionManager::GetActionManager();
    connect(pImageManager, &CImageManager::ImageUpdate, pActionManager, &CActionManager::CheckAllActions);

    CToolManager* pToolManager = CToolManager::GetToolManager();
    connect(pToolManager, &CToolManager::ToolChanged, pStatusBar, &CStatusBar::ToolUpdate);
    connect(pToolManager, &CToolManager::ToolChanged, pToolWidget, &CToolWidget::ToolChanged);

    QClipboard* pClipboard = QGuiApplication::clipboard();
    if (pClipboard != NULL)
    {
        connect(pClipboard, &QClipboard::dataChanged, m_pMainWindow, &MainWindow::UpdateActions);
    }
}
