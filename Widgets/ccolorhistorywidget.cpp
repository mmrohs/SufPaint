#include "ccolorhistorywidget.h"
#include <QPainter>

// show widget borders (only for debugging)
#define SHOW_BORDERS 1


CColorHistoryWidget::CColorHistoryWidget(QWidget *parent)
    : QWidget{parent}
{}

/*virtual*/ void CColorHistoryWidget::paintEvent(QPaintEvent* pEvent)
{
    QWidget::paintEvent(pEvent);

#ifdef SHOW_BORDERS
    static const QPen BPEN = QPen(QBrush(Qt::black), 3, Qt::DotLine);
    QPainter paint;
    paint.begin(this);
    paint.setPen(BPEN);
    paint.drawRect(QRect(0,0, width(), height()));
    paint.end();
#endif
}
