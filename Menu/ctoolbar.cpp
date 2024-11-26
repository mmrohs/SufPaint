#include "ctoolbar.h"
#include "../Management/cactionmanager.h"

CToolBar::CToolBar(QWidget* pParent)
    : QToolBar(tr("Toolbar"), pParent)
{
    setMovable(false);
    AddActions();
}

void CToolBar::AddActions()
{
    EnumActions actions[] =
        { FileNew, FileOpen, FileClose,
          Separator,
          FileSave, FileSaveAs,
          Separator,
          EditCopy, EditPaste, EditCut,
          Separator,
          EditUndo, EditRedo,
          Separator,
          ViewZoomIn, ViewZoomOut,
          Separator,
        };

    for (int i = 0; i < sizeof(actions)/sizeof(actions[0]); ++i)
    {
        if (actions[i] == Separator)
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
