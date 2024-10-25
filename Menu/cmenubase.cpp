#include "cmenubase.h"
#include "../EnumFunctions.h"
#include "../Management/cactionmanager.h"

CMenuBase::CMenuBase(const QString& title, QWidget* parent)
    : QMenu(title, parent)
{
    //connect(this, &QMenu::aboutToShow, this, &CMenuBase::AboutToShow);
}

QAction* CMenuBase::AddActionToMenu(EnumActions e)
{
    QAction* pAction = new QAction(GetActionName(e), this);

    // Add shortcut if available
    QKeySequence qkey = GetActionShortcut(e);
    if (qkey != QKeySequence::UnknownKey)
    {
        pAction->setShortcut(qkey);
    }

    // Add icon if available
    QIcon icon = GetActionIcon(e);
    if (!icon.isNull())
    {
        pAction->setIcon(icon);
    }

    // Add to ActionManager
    CActionManager* pActionManager = CActionManager::GetActionManager();
    if (pActionManager != NULL)
    {
        pActionManager->AddAction(e, pAction);
    }

    // Add to menu
    addAction(pAction);

    return pAction;
}

/*virtual void CMenuBase::AboutToShow()
{
    // override in derived classes!
}*/

#ifdef QT_DEBUG
void CMenuBase::ConnectAction(EnumActions e)
{
    CActionManager* pActionManager = CActionManager::GetActionManager();
    if (pActionManager != NULL)
    {
        QAction* pAction = pActionManager->FindAction(e);
        if (pAction != NULL)
        {
            connect(pAction, &QAction::triggered, this, &CMenuBase::DefaultAction);
        }
    }
}
#endif
