#include "debugtools.h"
#include <QPainter>


void DebugShowWidgetBorders(QWidget* widget)
{
#ifdef SHOW_BORDERS
    static const QPen BPEN = QPen(QBrush(Qt::black), 3, Qt::DotLine);
    QPainter paint;
    paint.begin(widget);
    paint.setPen(BPEN);
    paint.drawRect(QRect(0,0, widget->width(), widget->height()));
    paint.end();
#endif
}
