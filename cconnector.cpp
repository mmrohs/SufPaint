#include "cconnector.h"
#include <QClipboard>
#include "mainwindow.h"
#include "Widgets/cimageview.h"
#include "Widgets/ctoolwidget.h"
#include "Management/cactionmanager.h"
#include "Management/cimagemanager.h"
#include "Management/cselectionmanager.h"
#include "Management/ctoolmanager.h"


CConnector::CConnector(MainWindow* pMainWindow)
    : m_pMainWindow(pMainWindow)
{
    m_pImageView = NULL;
    m_pToolWidget = NULL;
    m_pStatusBar = NULL;
    m_pImageManager = NULL;
    m_pActionManager = NULL;
    m_pToolManager = NULL;
    m_pSelectionManager = NULL;
}

void CConnector::Init()
{
    // initialize widget pointers
    m_pImageView = m_pMainWindow->m_pImageView;
    m_pToolWidget = m_pMainWindow->m_pToolWidget;
    m_pStatusBar = m_pMainWindow->m_pStatusBar;

    // initialize managers
    m_pImageManager = CImageManager::GetImageManager();
    m_pActionManager = CActionManager::GetActionManager();
    m_pToolManager = CToolManager::GetToolManager();
    m_pSelectionManager = CSelectionManager::GetSelectionManager();
}

void CConnector::ConnectAll()
{
    Init();

    // CImageView signals
    connect(m_pImageView, &CImageView::ViewChanged, m_pStatusBar, &CStatusBar::ZoomUpdate);

    // CImageManager signals
    connect(m_pImageManager, &CImageManager::ImagePropertiesUpdate, m_pImageView, &CImageView::ImagePropertiesChanged);
    connect(m_pImageManager, &CImageManager::ImagePropertiesUpdate, m_pStatusBar, &CStatusBar::ImagePropertiesUpdate);
    connect(m_pImageManager, &CImageManager::ImagePropertiesUpdate, m_pToolWidget, &CToolWidget::ImagePropertiesChanged);
    connect(m_pImageManager, &CImageManager::ImagePropertiesUpdate, m_pActionManager, &CActionManager::CheckAllActions);
    connect(m_pImageManager, &CImageManager::ImagePropertiesUpdate, m_pSelectionManager, &CSelectionManager::ImagePropertiesChanged);
    connect(m_pImageManager, &CImageManager::ImagePixelsUpdate, m_pImageView, &CImageView::ImagePixelsChanged);

    // CToolManager signals
    connect(m_pToolManager, &CToolManager::ToolChanged, m_pStatusBar, &CStatusBar::ToolUpdate);
    connect(m_pToolManager, &CToolManager::ToolChanged, m_pToolWidget, &CToolWidget::ToolChanged);

    // CSelectionManager signals
    connect(m_pSelectionManager, &CSelectionManager::SelectionUpdate, m_pImageView, &CImageView::ImagePixelsChanged);
    connect(m_pSelectionManager, &CSelectionManager::SelectionUpdate, m_pActionManager, &CActionManager::CheckAllActions);
    connect(m_pSelectionManager, &CSelectionManager::SelectionUpdate, m_pStatusBar, &CStatusBar::SelectionUpdate);

    // clipboard signals
    QClipboard* pClipboard = QGuiApplication::clipboard();
    if (pClipboard != NULL)
    {
        connect(pClipboard, &QClipboard::dataChanged, m_pActionManager, &CActionManager::CheckAllActions);
    }
}
