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

void CTool::ProcessMousePressEvent(QMouseEvent* pEvent)
{
    if (pEvent->button() == Qt::LeftButton)
    {
        ProcessMouseLPressEvent(pEvent);
    }
    else if (pEvent->button() == Qt::RightButton)
    {
        ProcessMouseRPressEvent(pEvent);
    }
}

void CTool::ProcessMouseReleaseEvent(QMouseEvent* pEvent)
{
    if (pEvent->button() == Qt::LeftButton)
    {
        ProcessMouseLReleaseEvent(pEvent);
    }
    else if (pEvent->button() == Qt::RightButton)
    {
        ProcessMouseRReleaseEvent(pEvent);
    }
}

void CTool::ProcessMouseMoveEvent(QMouseEvent* pEvent)
{
    // Beware: button() always returns Qt::NoButton for MouseMove-Events
    ProcessMouseLMoveEvent(pEvent);
}

QImage* CTool::GetImage() const
{
    return CImageManager::GetImageManager()->GetImage();
}

QPoint CTool::GetImagePos(QPoint widgetPos) const
{
    return CImageViewManager::GetImageViewManager()->GetImagePos(widgetPos);
}

QPoint CTool::GetImagePos(QMouseEvent* pEvent, bool bCheck) const
{
    QPoint wdgPos = pEvent->pos();
    if (bCheck)
        wdgPos = CheckPositionInImageRect(wdgPos);
    return GetImagePos(wdgPos);
}

QPoint CTool::CheckPositionInImageRect(QPoint widgetPos) const
{
    return CImageViewManager::GetImageViewManager()->CheckPositionInImage(widgetPos);
}

QPoint CTool::GetMouseCoordinateFromEvent(QMouseEvent* pEvent) const
{
    QImage* pImage = GetImage();
    if (pImage != NULL)
    {
        QPoint imgPos = GetImagePos(pEvent, true);
        if (pImage->rect().contains(imgPos))
        {
            return imgPos;
        }
    }
    return QPoint(-1,-1);
}
