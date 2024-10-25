#include "cmenu.h"
#include "../mainwindow.h"
#include "ceditmenu.h"
#include "cfilemenu.h"
#include "cviewmenu.h"
#include "cimagemenu.h"
#include "cadjustmentmenu.h"
#include "chelpmenu.h"
#include <qmenubar.h>


CMenu::CMenu(class MainWindow* pParent)
    : m_pParent(pParent),
    m_pFileMenu(NULL), m_pEditMenu(NULL), m_pViewMenu(NULL),
    m_pImageMenu(NULL), m_pAdjustmentMenu(NULL), m_pHelpMenu(NULL)
{
    AddFileMenu();
    AddEditMenu();
    AddViewMenu();
    AddImageMenu();
    AddAdjustmentMenu();
    AddHelpMenu();
}

void CMenu::AddFileMenu()
{
    m_pFileMenu = new CFileMenu(QObject::tr("&File"), m_pParent);
    m_pParent->menuBar()->addMenu(m_pFileMenu);
}

void CMenu::AddEditMenu()
{
    m_pEditMenu = new CEditMenu(QObject::tr("&Edit"), m_pParent);
    m_pParent->menuBar()->addMenu(m_pEditMenu);
}

void CMenu::AddViewMenu()
{
    m_pViewMenu = new CViewMenu(QObject::tr("&View"), m_pParent);
    m_pParent->menuBar()->addMenu(m_pViewMenu);
}

void CMenu::AddImageMenu()
{
    m_pImageMenu = new CImageMenu(QObject::tr("&Image"), m_pParent);
    m_pParent->menuBar()->addMenu(m_pImageMenu);
}

void CMenu::AddAdjustmentMenu()
{
    m_pAdjustmentMenu = new CAdjustmentMenu(QObject::tr("&Adjustments"), m_pParent);
    m_pParent->menuBar()->addMenu(m_pAdjustmentMenu);
}

void CMenu::AddHelpMenu()
{
    m_pHelpMenu = new CHelpMenu(QObject::tr("&Help"), m_pParent);
    m_pParent->menuBar()->addMenu(m_pHelpMenu);
}
