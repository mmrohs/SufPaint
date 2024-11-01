#include "ccolorwidget.h"
#include <QBoxLayout>
#include "ccolorpreviewwidget.h"
#include "ccolorrgbawidget.h"
#include "ccolorpalettewidget.h"
#include "ccolorhistorywidget.h"
#include "../Misc/debugtools.h"
#include "../Management/ccolormanager.h"

#define WIDTH 150


CColorWidget::CColorWidget(QWidget* pParent)
    : QGroupBox(tr("Colors"), pParent),
    m_pColPrevWidget(NULL), m_pColHistWidget(NULL), m_pColRgbaWidget(NULL), m_pColPalWidget(NULL)
{
    setMinimumWidth(WIDTH);
    setMaximumWidth(WIDTH);

    AddLayout();
    AddConnections();

    ColorChanged();
}

void CColorWidget::ColorChanged()
{
    emit ColorUpdate();
    update();
}

void CColorWidget::AddLayout()
{
    // create the widgets
    m_pColPrevWidget = new CColorPreviewWidget(this);
    m_pColHistWidget = new CColorHistoryWidget(this);
    m_pColRgbaWidget = new CColorRgbaWidget(this);
    m_pColPalWidget = new CColorPaletteWidget(this);

    // vertical layout inside the horizontal layout
    QVBoxLayout* vhbox = new QVBoxLayout();
    vhbox->addWidget(m_pColPrevWidget, 6);
    vhbox->addWidget(m_pColHistWidget, 7);
    vhbox->setSpacing(2);

    // horizontal layout on top
    QHBoxLayout* hbox = new QHBoxLayout();
    hbox->addLayout(vhbox, 9);
    hbox->addWidget(m_pColRgbaWidget, 7);

    // setup the final layout
    QVBoxLayout* vbox = new QVBoxLayout();
    vbox->addLayout(hbox, 1);
    vbox->addWidget(m_pColPalWidget, 5);
    //vbox->addWidget(m_pChkLight, 1);

    setLayout(vbox);
}

void CColorWidget::AddConnections()
{
    // this -> child widgets
    connect(this, &CColorWidget::ColorUpdate, m_pColPrevWidget, &CColorPreviewWidget::ColorChanged);
    connect(this, &CColorWidget::ColorUpdate, m_pColRgbaWidget, &CColorRgbaWidget::ColorChanged);
    connect(this, &CColorWidget::ColorUpdate, m_pColPalWidget,  &CColorPaletteWidget::ColorChanged);

    // CColorManager -> this
    connect(CColorManager::GetColorManager(), &CColorManager::ColorUpdate, this, &CColorWidget::ColorChanged);
}

/*virtual*/ void CColorWidget::paintEvent(QPaintEvent* pEvent)
{
    QGroupBox::paintEvent(pEvent);

#ifdef QT_DEBUG
    DebugShowWidgetBorders(this);
#endif
}
