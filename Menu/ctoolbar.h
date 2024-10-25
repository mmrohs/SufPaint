#ifndef CTOOLBAR_H
#define CTOOLBAR_H

#include <QToolBar>
#include "../EnumFunctions.h"

class CToolBar : public QToolBar
{
public:
    explicit CToolBar(QWidget* pParent);

protected:
    void AddActions();

private:
    void AddAction(EnumActions e);
};

#endif // CTOOLBAR_H
