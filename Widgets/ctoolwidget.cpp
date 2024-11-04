#include "ctoolwidget.h"
#include <QGridLayout>
#include <QToolButton>
#include "ctoolbutton.h"
//#include "../Management/ctoolmanager.h"

// fixed widget width
#define WIDTH 150


CToolWidget::CToolWidget(QWidget* pParent)
    : QGroupBox(tr("Tools"), pParent),
    m_pGridLayout(NULL), m_bEnabled(false)
{
    setMinimumWidth(WIDTH);
    setMaximumWidth(WIDTH);

    AddLayout();
    EnableTools();
}

void CToolWidget::SetEnabled(bool bEnabled)
{
    bool bUpdate = m_bEnabled != bEnabled;
    m_bEnabled = bEnabled;
    if (bUpdate)
        EnableTools();
}

void CToolWidget::ToolChanged()
{
    for (int i = 0; i < m_vecTools.size(); ++i)
    {
        m_vecTools[i]->ToolChanged();
    }
}

void CToolWidget::AddLayout()
{
    m_pGridLayout = new QGridLayout();

    AddToolButtons();

    m_pGridLayout->setColumnStretch(0, 1);
    m_pGridLayout->setColumnStretch(1, 1);
    m_pGridLayout->setColumnStretch(2, 1);

    QVBoxLayout* vbox = new QVBoxLayout();
    vbox->addLayout(m_pGridLayout, 1);
    vbox->addStretch(15);

    setLayout(vbox);
}

void CToolWidget::AddToolButtons()
{
    EnumTools tools[] = { ToolRectSelect, ToolColorPicker, ToolBrush,
                          ToolPencil, ToolBucket, ToolGradient,
                          ToolLine
                         /*, ... to do ... */ };

    for (int i = 0; i < sizeof(tools)/sizeof(tools[0]); ++i)
    {
        CToolButton* pButton = new CToolButton(tools[i], this);
        //pButton->setStyleSheet("border: none");
        m_pGridLayout->addWidget(pButton, i / 3, i % 3);
        m_vecTools.push_back(pButton);
    }
}

void CToolWidget::EnableTools()
{
    for (int i = 0; i < m_vecTools.size(); ++i)
    {
        m_vecTools[i]->setEnabled(m_bEnabled);
    }
}
