#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qboxlayout.h>
#include <qgraphicsview.h>
#include <QGroupBox>
#include <QClipboard>
#include "Management/cactionmanager.h"
#include "Management/cimagemanager.h"
#include "Management/ctoolmanager.h"
#include "Menu/cmenu.h"
#include "Menu/ctoolbar.h"
#include "Widgets/cimageview.h"
#include "Widgets/clayerwidget.h"
#include "Widgets/ctoolwidget.h"
#include "Widgets/ccolorwidget.h"


MainWindow::MainWindow(QWidget* pParent)
    : QMainWindow(pParent), m_pUI(new Ui::MainWindow),
    m_pImageView(NULL), m_pToolWidget(NULL), m_pLayerWidget(NULL), m_pColorWidget(NULL),
    m_pMenu(NULL), m_pToolBar(NULL), m_pStatusBar(NULL)
{
    m_pUI->setupUi(this);

    AddMenu();
    AddToolbar();
    AddStatusBar();
    AddLayout();
    AddConnections();

    CImageManager* pImageManager = CImageManager::GetImageManager();
    if (pImageManager != NULL)
    {
        pImageManager->SetImageView(m_pImageView);
    }
}

MainWindow::~MainWindow()
{
    delete m_pUI;
}

void MainWindow::UpdateActions()
{
    CActionManager* pActionManager = CActionManager::GetActionManager();
    if (pActionManager != NULL)
    {
        pActionManager->CheckAllActions();
    }
}

void MainWindow::AddMenu()
{
    m_pMenu = new CMenu(this);
}

void MainWindow::AddToolbar()
{
    m_pToolBar = new CToolBar(this);
    addToolBar(Qt::TopToolBarArea, m_pToolBar);
}

void MainWindow::AddStatusBar()
{
    m_pStatusBar = new CStatusBar(this);
}

void MainWindow::AddLayout()
{
    m_pToolWidget = new CToolWidget(this);
    m_pColorWidget = new CColorWidget(this);
    m_pImageView = new CImageView(this);
    m_pLayerWidget = new CLayerWidget(this);

    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->addWidget(m_pToolWidget, 1);
    vlayout->addWidget(m_pColorWidget, 1);

    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->addLayout(vlayout);
    hlayout->addWidget(m_pImageView);
    hlayout->addWidget(m_pLayerWidget);
    m_pUI->centralwidget->setLayout(hlayout);
}

void MainWindow::AddConnections()
{
    connect(m_pImageView, &CImageView::imageChanged, m_pStatusBar, &CStatusBar::ImageUpdate);
    connect(m_pImageView, &CImageView::imageChanged, m_pToolWidget, &CToolWidget::SetEnabled);
    connect(m_pImageView, &CImageView::scaleChanged, m_pStatusBar, &CStatusBar::ZoomUpdate);

    CToolManager* pToolManager = CToolManager::GetToolManager();
    if (pToolManager != NULL)
    {
        connect(pToolManager, &CToolManager::ToolChanged, m_pStatusBar, &CStatusBar::ToolUpdate);
        connect(pToolManager, &CToolManager::ToolChanged, m_pToolWidget, &CToolWidget::ToolChanged);
    }

    QClipboard* pClipboard = QGuiApplication::clipboard();
    if (pClipboard != NULL)
    {
        connect(pClipboard, &QClipboard::dataChanged, this, &MainWindow::UpdateActions);
    }
}
