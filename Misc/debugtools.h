#ifndef DEBUGTOOLS_H
#define DEBUGTOOLS_H

#include <QWidget>

// show widget borders (only for debugging)
#ifdef QT_DEBUG
//#define SHOW_BORDERS
#endif

void DebugShowWidgetBorders(QWidget* widget);

#endif // DEBUGTOOLS_H
