#include "cstatusbar.h"
#include <QStatusBar>
#include "cstatusbarimagelabel.h"
#include "cstatusbartoollabel.h"
#include "cstatusbarzoomlabel.h"
#include "../mainwindow.h"


CStatusBar::CStatusBar(class MainWindow* pParent)
    : m_pParent(pParent),
    m_pSBImageLabel(NULL), m_pSBToolLabel(NULL), m_pSBZoomLabel(NULL)
{
    AddStatusBarItems();
}

void CStatusBar::AddStatusBarItems()
{
    m_pSBToolLabel = new CStatusBarToolLabel(m_pParent);
    m_pParent->statusBar()->addPermanentWidget(m_pSBToolLabel, 14);

    m_pSBImageLabel = new CStatusBarImageLabel(m_pParent);
    m_pParent->statusBar()->addPermanentWidget(m_pSBImageLabel, 3);

    m_pSBZoomLabel = new CStatusBarZoomLabel(m_pParent);
    m_pParent->statusBar()->addPermanentWidget(m_pSBZoomLabel, 2);
}

void CStatusBar::ImageUpdate()
{
    CStatusBarImageLabel* pImageLabel = (CStatusBarImageLabel*)m_pSBImageLabel;
    pImageLabel->Update();
}

void CStatusBar::ToolUpdate()
{
    CStatusBarToolLabel* pToolLabel = (CStatusBarToolLabel*)m_pSBToolLabel;
    pToolLabel->Update();
}

void CStatusBar::ZoomUpdate()
{
    CStatusBarZoomLabel* pZoomLabel = (CStatusBarZoomLabel*)m_pSBZoomLabel;
    pZoomLabel->Update();
}
