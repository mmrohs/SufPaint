#ifndef CHELPMENU_H
#define CHELPMENU_H

#include "cmenubase.h"

class CHelpMenu : public CMenuBase
{
public:
    explicit CHelpMenu(const QString& title, QWidget* pParent);

protected:
    void AddActions();
    void AddConnections();
};

#endif // CHELPMENU_H
