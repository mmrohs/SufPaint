#include "ctool.h"
#include "../Management/cimagemanager.h"
#include "../Management/CImageViewManager.h"


CTool::CTool(EnumTools eTool)
    : m_eTool(eTool)
{
}

/*virtual*/ CTool::~CTool()
{
}

EnumTools CTool::GetToolEnum() const
{
    return m_eTool;
}

/*virtual*/ void CTool::ProcessMouseReleaseEvent(QMouseEvent* pEvent)
{
    // add implementation in derived class if necessary
}

/*virtual*/ void CTool::ProcessMouseMoveEvent(QMouseEvent* pEvent)
{
    // add implementation in derived class if necessary
}

QImage* CTool::GetImage() const
{
    CImageManager* pImageManager = CImageManager::GetImageManager();
    if (pImageManager != NULL)
    {
        return pImageManager->GetImage();
    }
    return NULL;
}

QPoint CTool::GetImagePos(QMouseEvent* pEvent, bool bCheckPosition)
{
    QPointF posF = pEvent->position();
    QPoint widgetPos (posF.x(), posF.y());
    return CImageViewManager::GetImageViewManager()->GetImagePos(widgetPos, bCheckPosition);
}
