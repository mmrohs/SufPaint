#include "ccolorpreviewwidget.h"
#include <QPen>
#include <QPainter>
#include <QMouseEvent>

// show widget border (only for debug)
#define SHOW_BORDERS 1

// constants for the preview rects
#define DIST 10     // distance between rects
#define SIZE 28     // size of the rects
#define GAP 3       // border gap


CColorPreviewWidget::CColorPreviewWidget(QWidget *parent)
    : QWidget{parent}
{
}

void CColorPreviewWidget::SetForegroundColor(QColor color)
{
    m_foregroundColor = color;
    update();
}

void CColorPreviewWidget::SetBackgroundColor(QColor color)
{
    m_backgroundColor = color;
    update();
}

/*virtual*/ void CColorPreviewWidget::paintEvent(QPaintEvent* pEvent)
{
    // Draw color filled rects for the foreground and background color
    static const QPoint TL = QPoint(4, 10); // top-left corner
    static const QRect rectB(TL.x() + DIST, TL.y(), SIZE, SIZE);
    static const QRect rectF(TL.x(), TL.y() + DIST, SIZE, SIZE);
    DrawColorRect(rectB, m_backgroundColor);
    DrawColorRect(rectF, m_foregroundColor);

    // Save the bounding rectangle for the switch button
    m_rectFB = rectB.united(rectF);

#ifdef SHOW_BORDERS
    static const QPen BPEN = QPen(QBrush(Qt::black), 3, Qt::DotLine);
    QPainter paint;
    paint.begin(this);
    paint.setPen(BPEN);
    paint.drawRect(QRect(0,0, width(), height()));
    paint.end();
#endif
}

/*virtual*/ void CColorPreviewWidget::mousePressEvent(QMouseEvent* pEvent)
{
    QPointF pos = pEvent->position();
    QPoint mousePos(pos.x(), pos.y());
    if (m_rectFB.contains(mousePos))
    {
        QColor backgroundColor = m_backgroundColor;
        m_backgroundColor = m_foregroundColor;
        m_foregroundColor = backgroundColor;
        emit ColorsSwitched();
    }
}

/* Draws a color filled rect with a black border
 */
void CColorPreviewWidget::DrawColorRect(QRect rect, QColor color)
{
    static const QPen BPEN = QPen(QBrush(Qt::black), 3, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
    static const QPen WPEN = QPen(QBrush(Qt::white), 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);

    // calculate border rects
    QRect rectOuter(rect.x() - GAP, rect.y() - GAP, rect.width() + 2 * GAP, rect.height() + 2 * GAP);
    QRect rectInner(rect.x() - GAP + 2, rect.y() - GAP + 2, rect.width() + 2 * GAP - 4, rect.height() + 2 * GAP - 4);

    // draw border and selected color rects
    QPainter paint;
    paint.begin(this);
    paint.setPen(BPEN);
    paint.drawRect(rectOuter);
    paint.setPen(WPEN);
    paint.drawRect(rectInner);
    paint.fillRect(rect, QBrush(color));
    paint.end();
}
