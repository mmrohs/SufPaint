#include "ccolorhistorywidget.h"
#include <QPainter>
#include <QMouseEvent>
#include "../Misc/debugtools.h"

// constants for the color rects
#define TL QPoint(1, 10)        // top-left corner
#define SIZE 13                 // size of the rects
#define DIST 2                  // distance between rects
#define STEP (SIZE + DIST)      // distance between topleft corners of rects


CColorHistoryWidget::CColorHistoryWidget(QWidget *parent)
    : QWidget{parent}
{
    ResetColors();
    SetRects();
}

void CColorHistoryWidget::AddColorToHistory(QColor color)
{
    ShiftColors();
    m_colors[0] = color;
}

void CColorHistoryWidget::ResetColors()
{
    for (int i = 0; i < NCOLORS; ++i)
    {
        m_colors[i] = QColor(255 * (1 - (double)i/NCOLORS), 0, 0);
    }
}

// All the colors move by one towards the end of the array
void CColorHistoryWidget::ShiftColors()
{
    for (int i = 0; i + 1 < NCOLORS; ++i)
    {
        m_colors[i + 1] = m_colors[i];
    }
}

void CColorHistoryWidget::SetRects()
{
    static const QSize QSIZE = QSize(SIZE,SIZE);

    for (int i = 0; i < NCOLORS; ++i)
    {
        int x = TL.x() + (i % 3) * STEP;
        int y = TL.y() + (i / 3) * STEP;
        m_colorRects[i] = QRect(QPoint(x,y), QSIZE);
    }
}

/*virtual*/ void CColorHistoryWidget::paintEvent(QPaintEvent* pEvent)
{
    QWidget::paintEvent(pEvent);

    // draw the historical colors in a 3x3 grid
    QPainter paint;
    paint.begin(this);
    for (int i = 0; i < NCOLORS; ++i)
    {
        paint.fillRect(m_colorRects[i], QBrush(m_colors[i]));
    }
    paint.end();

#ifdef QT_DEBUG
    DebugShowWidgetBorders(this);
#endif
}

/*virtual*/ void CColorHistoryWidget::mousePressEvent(QMouseEvent* pEvent)
{
    QPointF posF = pEvent->position();
    QPoint pos(posF.x(), posF.y());
    for (int i = 0; i < NCOLORS; ++i)
    {
        if (m_colorRects[i].contains(pos))
        {
            emit ColorPicked(m_colors[i]);
            break;
        }
    }
}
