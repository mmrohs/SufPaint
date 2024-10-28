#include "ccolorwidget.h"
#include <QPainter>
#include <QPaintEvent>

// fixed widget size
#define WIDTH 150
#define HEIGHT 150


CColorWidget::CColorWidget(QWidget* pParent)
    : QGroupBox(tr("Colors"), pParent)
{
    setMinimumWidth(WIDTH);
    setMaximumWidth(HEIGHT);

    m_selectedColor = Qt::black;
}

void CColorWidget::ColorPicked(QColor color)
{
    m_selectedColor = color;
    update();
}

/*virtual*/ void CColorWidget::paintEvent(QPaintEvent* pEvent)
{
    QGroupBox::paintEvent(pEvent);

    QPainter paint;
    paint.begin(this);
    paint.setClipRect(pEvent->rect());
    paint.fillRect(QRect(20,30,30,30), QBrush(m_selectedColor));
    paint.end();
}
