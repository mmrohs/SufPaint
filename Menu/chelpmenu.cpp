#include "chelpmenu.h"

CHelpMenu::CHelpMenu(const QString& title, QWidget* parent)
    : CMenuBase(title, parent)
{
    AddActions();
    AddConnections();
}

void CHelpMenu::AddActions()
{
    AddActionToMenu(HelpInfo);
}

void CHelpMenu::AddConnections()
{
    ConnectAction(HelpInfo);
}
