#ifndef CMENUBASE_H
#define CMENUBASE_H

#include <QMenu>
#include "../EnumFunctions.h"

class CMenuBase : public QMenu
{
public:
    explicit CMenuBase(const QString& title, QWidget* parent);

protected:
    QAction* AddActionToMenu(EnumActions e);

    //virtual void AboutToShow();

#ifdef QT_DEBUG
    // connect to placeholder function below
    void ConnectAction(EnumActions e);

private slots:
    void DefaultAction() { qDebug() << "CMenuBase::DefaultAction()"; }
#endif

};

#endif // CMENUBASE_H
