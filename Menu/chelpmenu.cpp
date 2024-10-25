#include "chelpmenu.h"

CHelpMenu::CHelpMenu(const QString& title, QWidget* parent)
    : CMenuBase(title, parent)
{
    AddActions();
    AddConnections();
}

void CHelpMenu::AddActions()
{
    AddActionToMenu(ActionHelpInfo);
}

void CHelpMenu::AddConnections()
{
    ConnectAction(ActionHelpInfo);
}
