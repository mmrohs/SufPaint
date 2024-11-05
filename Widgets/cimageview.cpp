#include "cimageview.h"
#include <QPainter>
#include <QPaintEvent>
#include "../Management/cimagemanager.h"
#include "../Management/ctoolmanager.h"
#include "../Tools/ctool.h"


CImageView::CImageView(QWidget* pParent)
    : QWidget(pParent),
    m_trafo(this)
{
}

qreal CImageView::GetZoom() const
{
    return 100.0 * m_trafo.GetScale();
}

void CImageView::ZoomIn()
{
    m_trafo.SetNextScale();
    emit ViewChanged();
    update();
}

void CImageView::ZoomOut()
{
    m_trafo.SetPrevScale();
    emit ViewChanged();
    update();
}

void CImageView::ResetZoom()
{
    m_trafo.ResetScale();
    emit ViewChanged();
    update();
}

const CImageViewTransform* CImageView::GetTrafo() const
{
    return &m_trafo;
}

void CImageView::ImageChanged()
{
    update();
}

CTool* CImageView::GetActiveTool()
{
    CToolManager* pToolManager = CToolManager::GetToolManager();
    if (pToolManager != NULL)
    {
        return pToolManager->GetActiveTool();
    }
    return NULL;
}

/*virtual*/ void CImageView::paintEvent(QPaintEvent* pEvent)
{
    static const QBrush backgroundBrush = QBrush(QColor(120, 120, 120));

    CImageManager* pImageManager = CImageManager::GetImageManager();
    if (pImageManager == NULL)
        return;

    QPainter paint;
    paint.begin(this);
    paint.setClipRect(pEvent->rect());
    paint.fillRect(pEvent->rect(), backgroundBrush);
    if (pImageManager->HasImage())
    {
        QPointF pos = m_trafo.GetImageOrigin();
        qreal scale = m_trafo.GetScale();
        paint.scale(scale, scale);
        paint.drawImage(pos, *pImageManager->GetImage());
    }
    paint.end();
}

/*virtual*/ void CImageView::wheelEvent(QWheelEvent* pEvent)
{
    int delta_y = pEvent->angleDelta().y();
    if (delta_y > 0)
    {
        ZoomIn();
    }
    else
    {
        ZoomOut();
    }
    pEvent->accept();
}

/*virtual*/ void CImageView::mousePressEvent(QMouseEvent* pEvent)
{
    CTool* pTool = GetActiveTool();
    if (pTool != NULL)
    {
        QPoint widgetPos (pEvent->position().x(), pEvent->position().y());
        //QPoint imagePos = TransformWidgetPosToImagePos(widgetPos);
        pTool->ProcessMousePressEvent(pEvent, this);
        pEvent->accept();
    }
    else
    {
        pEvent->ignore();
    }
}

/*virtual*/ void CImageView::mouseReleaseEvent(QMouseEvent* pEvent)
{
    CTool* pTool = GetActiveTool();
    if (pTool != NULL)
    {
        QPoint widgetPos (pEvent->position().x(), pEvent->position().y());
        //QPoint imagePos = TransformWidgetPosToImagePos(widgetPos);
        pTool->ProcessMouseReleaseEvent(pEvent, this);
        pEvent->accept();
    }
    else
    {
        pEvent->ignore();
    }
}

/*virtual*/ void CImageView::mouseMoveEvent(QMouseEvent* pEvent)
{
    CTool* pTool = GetActiveTool();
    if (pTool != NULL)
    {
        QPoint widgetPos (pEvent->position().x(), pEvent->position().y());
        //QPoint imagePos = TransformWidgetPosToImagePos(widgetPos);
        pTool->ProcessMouseMoveEvent(pEvent, this);
        pEvent->accept();
    }
    else
    {
        pEvent->ignore();
    }
}
