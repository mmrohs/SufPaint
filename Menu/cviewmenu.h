#ifndef CVIEWMENU_H
#define CVIEWMENU_H

#include "cmenubase.h"

class CViewMenu : public CMenuBase
{
public:
    explicit CViewMenu(const QString& title, QWidget* parent);

protected:
    void AddActions();
    void AddConnections();

    template<typename func>
    void ConnectAction(EnumActions e, func&& slot);

private slots:
    void ZoomIn();
    void ZoomOut();
    void ResetZoom();
};

#endif // CVIEWMENU_H
