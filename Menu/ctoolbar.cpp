#include "ctoolbar.h"
#include "../cactionmanager.h"

CToolBar::CToolBar(QWidget* pParent)
    : QToolBar(tr("Toolbar"), pParent)
{
    setMovable(false);
    AddActions();
}

void CToolBar::AddActions()
{
    EnumActions actions[] =
        { ActionFileNew, ActionFileOpen, ActionFileClose,
          ActionSeparator,
          ActionFileSave, ActionFileSaveAs,
          ActionSeparator,
          ActionEditCopy, ActionEditPaste, ActionEditCut,
          ActionSeparator,
          ActionEditUndo, ActionEditRedo,
          ActionSeparator,
          ActionViewZoomIn, ActionViewZoomOut,
          ActionSeparator,
        };

    for (int i = 0; i < sizeof(actions)/sizeof(actions[0]); ++i)
    {
        if (actions[i] == ActionSeparator)
            addSeparator();
        else
            AddAction(actions[i]);
    }
}

void CToolBar::AddAction(EnumActions e)
{
    CActionManager* pActionManager = CActionManager::GetActionManager();
    if (pActionManager != NULL)
    {
        QAction* pAction = pActionManager->FindAction(e);
        if (pAction != NULL)
        {
            addAction(pAction);
        }
    }
}
