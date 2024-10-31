#include "ccolorwidget.h"
#include <QBoxLayout>
#include "ccolorpreviewwidget.h"
#include "ccolorrgbawidget.h"
#include "ccolorpalettewidget.h"
#include "ccolorhistorywidget.h"
#include "../Misc/debugtools.h"

#define WIDTH 150
#define RGBAMIN 0
#define RGBAMAX 255


CColorWidget::CColorWidget(QWidget* pParent)
    : QGroupBox(tr("Colors"), pParent),
    m_pColPrevWidget(NULL), m_pColHistWidget(NULL), m_pColRgbaWidget(NULL), m_pColPalWidget(NULL)
{
    setMinimumWidth(WIDTH);
    setMaximumWidth(WIDTH);

    AddLayout();
    AddConnections();

    ColorPickedRgba(Qt::white);
    ColorsSwitched();
    ColorPickedRgba(Qt::black);
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
    // CColorPreviewWidget <-> this
    connect(this, &CColorWidget::UpdateForegroundColor, m_pColPrevWidget, &CColorPreviewWidget::SetForegroundColor);
    connect(this, &CColorWidget::UpdateBackgroundColor, m_pColPrevWidget, &CColorPreviewWidget::SetBackgroundColor);
    connect(m_pColPrevWidget, &CColorPreviewWidget::ColorsSwitched, this, &CColorWidget::ColorsSwitched);

    // CColorRgbaWidget <-> this
    connect(this, &CColorWidget::UpdateForegroundColor, m_pColRgbaWidget, &CColorRgbaWidget::SetColor);
    connect(m_pColRgbaWidget, &CColorRgbaWidget::ColorChanged, this, &CColorWidget::ColorPickedRgba);

    // CColorPaletteWidget -> this
    connect(m_pColPalWidget, &CColorPaletteWidget::ColorPicked, this, &CColorWidget::ColorPickedRgb);

    // CColorHistoryWidget -> this
    connect(m_pColHistWidget, &CColorHistoryWidget::ColorPicked, this, &CColorWidget::ColorPickedRgb);
}

// Sets the foreground color to the parameter color, but ignores its alpha value
void CColorWidget::ColorPickedRgb(QColor color)
{
    ColorPickedRgba(QColor(color.red(), color.green(), color.blue(), m_foregroundColor.alpha()));
}

// Sets the foreground color to the parameter color
void CColorWidget::ColorPickedRgba(QColor color)
{
    m_foregroundColor = color;
    update();
    emit UpdateForegroundColor(m_foregroundColor);
}

void CColorWidget::ColorsSwitched()
{
    QColor foregroundColor = m_foregroundColor;
    m_foregroundColor = m_backgroundColor;
    m_backgroundColor = foregroundColor;

    emit UpdateForegroundColor(m_foregroundColor);
    emit UpdateBackgroundColor(m_backgroundColor);
}

/*virtual*/ void CColorWidget::paintEvent(QPaintEvent* pEvent)
{
    QGroupBox::paintEvent(pEvent);

#ifdef QT_DEBUG
    DebugShowWidgetBorders(this);
#endif
}
