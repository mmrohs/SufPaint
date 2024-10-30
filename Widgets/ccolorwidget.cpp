#include "ccolorwidget.h"
/*#include <QLabel>
#include <QSpinBox>
#include <QGridLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QPen>*/
#include <QBoxLayout>
#include <QCheckBox>
#include "ccolorpreviewwidget.h"
#include "ccolorrgbawidget.h"
#include "ccolorpalettewidget.h"
#include "ccolorhistorywidget.h"

#define WIDTH 150
#define RGBAMIN 0
#define RGBAMAX 255


CColorWidget::CColorWidget(QWidget* pParent)
    : QGroupBox(tr("Colors"), pParent),
    m_pColPrevWidget(NULL), m_pColHistWidget(NULL), m_pColRgbaWidget(NULL), m_pColPalWidget(NULL), m_pChkLight(NULL),
    m_foregroundColor(Qt::black), m_backgroundColor(Qt::white)
{
    setMinimumWidth(WIDTH);
    setMaximumWidth(WIDTH);

    AddLayout();
    AddConnections();

    emit UpdateForegroundColor(m_foregroundColor);
    emit UpdateBackgroundColor(m_backgroundColor);
}

void CColorWidget::AddLayout()
{
    // create the widgets
    m_pColPrevWidget = new CColorPreviewWidget(this);
    m_pColHistWidget = new CColorHistoryWidget(this);
    m_pColRgbaWidget = new CColorRgbaWidget(this);
    m_pColPalWidget = new CColorPaletteWidget(this);

    // create the checkbox for switching to light mode
    m_pChkLight = new QCheckBox(tr("Light Palette"), this);


    // vertical layout inside the horizontal layout
    QVBoxLayout* vhbox = new QVBoxLayout();
    vhbox->addWidget(m_pColPrevWidget, 1);
    vhbox->addWidget(m_pColHistWidget, 1);

    // horizontal layout on top
    QHBoxLayout* hbox = new QHBoxLayout();
    hbox->addLayout(vhbox, 9);
    hbox->addWidget(m_pColRgbaWidget, 7);

    // setup the final layout
    QVBoxLayout* vbox = new QVBoxLayout();
    vbox->addLayout(hbox, 1);
    vbox->addWidget(m_pColPalWidget, 5);
    vbox->addWidget(m_pChkLight, 1);

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

    // QCheckBox -> this
    connect(m_pChkLight, &QCheckBox::checkStateChanged, m_pColPalWidget, &CColorPaletteWidget::SetLightMode);
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
