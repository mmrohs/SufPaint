#include "cactionmanager.h"
#include <QGuiApplication>
#include "cimagemanager.h"
#include "cselectionmanager.h"
#include <QClipboard>
#include <QMimeData>

/*static*/ CActionManager* CActionManager::m_pSingletonInstance = NULL;

CActionManager::CActionManager()
{
}

/*static*/ CActionManager* CActionManager::GetActionManager()
{
    if (m_pSingletonInstance == NULL)
    {
        m_pSingletonInstance = new CActionManager();
    }
    return m_pSingletonInstance;
}

void CActionManager::AddAction(EnumActions e, QAction* pAction)
{
    if (e <= ActionDefault || e >= ActionEnd)
    {
        qDebug() << "CActionManager::AddAction(): invalid action added";
    }
    else if (pAction == NULL)
    {
        qDebug() << "CActionManager::AddAction(): null action added";
    }
    else
    {
        m_actionMap[e] = pAction;
        CheckAction(e);
    }
}

void CActionManager::RemoveAction(EnumActions e)
{
    auto iter = m_actionMap.find(e);
    if (iter != m_actionMap.end())
    {
        m_actionMap.erase(iter);
    }
}

QAction* CActionManager::FindAction(EnumActions e)
{
    auto iter = m_actionMap.find(e);
    if (iter != m_actionMap.end())
    {
        return iter->second;
    }
    return NULL;
}

void CActionManager::CheckAllActions()
{
    for (auto iter : m_actionMap)
    {
        CheckAction(iter.first);
    }
}

void CActionManager::CheckAction(EnumActions e)
{
    QAction* pAction = FindAction(e);
    if (pAction != NULL)
    {
        CheckAction(pAction, e);
    }
}

/* function checks whether an action can be enabled
 * to do: move to a new class
*/
void CActionManager::CheckAction(QAction* pAction, EnumActions e)
{
    if (pAction == NULL)
        return;

    bool bEnabled = false;

    switch (e) {
    // always enabled actions:
    case ActionFileNew:
    case ActionFileOpen:
    case ActionFileQuit:
    case ActionViewZoomIn:
    case ActionViewZoomOut:
    case ActionViewOrigSize:
    case ActionHelpInfo:
        bEnabled = true;
        break;
    // always disabled actions
    case ActionEditUndo:
    case ActionEditRedo:
        bEnabled = false;
        break;
    // actions that require an opened image:
    case ActionFileClose:
    case ActionFileSave:
    case ActionFileSaveAs:
    case ActionEditCopy:
    case ActionImageResize:
    case ActionImageResizeCanvas:
    case ActionImageRotate90C:
    case ActionImageRotate90CC:
    case ActionImageRotate180:
    case ActionImageMirrorHor:
    case ActionImageMirrorVer:
    case ActionAdjustInvert:
    case ActionAdjustGrayscale:
    case ActionAdjustSepia:
    {
        bEnabled = CImageManager::GetImageManager()->HasImage();
        break;
    }
    // actions that require an image in the clipboard:
    case ActionEditPaste:
    {
        QClipboard* pClipboard = QGuiApplication::clipboard();
        if (pClipboard != NULL)
        {
            const QMimeData* pMimeData = pClipboard->mimeData();
            bEnabled = pMimeData != NULL && pMimeData->hasImage();
        }
        break;
    }
    // actions that require an image and a selection:
    case ActionEditCut:
    case ActionImageCropSelection:
    {
        bEnabled = CImageManager::GetImageManager()->HasImage();
        bEnabled = bEnabled && CSelectionManager::GetSelectionManager()->HasSelection();
        break;
    }
    default:
        qDebug() << "CActionManager::CheckAction(): unknown enumeration value" << e;
    }

    pAction->setEnabled(bEnabled);
}
