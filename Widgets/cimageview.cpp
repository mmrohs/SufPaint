#include "cimageview.h"
#include <QPainter>
#include <QPaintEvent>
#include "../Management/cimagemanager.h"
#include "../Management/ctoolmanager.h"
#include "../Tools/ctool.h"


CImageView::CImageView(QWidget* pParent)
    : QWidget(pParent),
    m_pImage(NULL), m_trafo(this)
{
}

void CImageView::SetImage(QImage* pImage)
{
    m_pImage = pImage;
    m_trafo.AutoScale();
    //emit imageChanged(m_pImage != NULL);
}

bool CImageView::HasImage() const
{
    return m_pImage != NULL;
}

QSize CImageView::GetImageSize() const
{
    return m_pImage->size();
}

QRect CImageView::GetImageRect() const
{
    return m_pImage->rect();
}

void CImageView::ZoomIn()
{
    m_trafo.SetNextScale();
}

void CImageView::ZoomOut()
{
    m_trafo.SetPrevScale();
}

void CImageView::ResetZoom()
{
    m_trafo.ResetScale();
}

const CImageViewTransform* CImageView::GetTrafo() const
{
    return &m_trafo;
}

CTool* CImageView::GetActiveTool()
{
    if (m_pImage == NULL)
        return NULL;

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

    QPainter paint;
    paint.begin(this);
    paint.setClipRect(pEvent->rect());
    paint.fillRect(pEvent->rect(), backgroundBrush);
    if (m_pImage != NULL)
    {
        qreal scale = m_trafo.GetScale();
        QPointF posOrigin = m_trafo.GetImageOrigin();
        paint.scale(scale, scale);
        paint.drawImage(posOrigin, *m_pImage);
    }
    paint.end();
}

/*virtual*/ void CImageView::wheelEvent(QWheelEvent* pEvent)
{
    CImageManager* pImageManager = CImageManager::GetImageManager();
    if (pImageManager != NULL)
    {
        int delta_y = pEvent->angleDelta().y();
        if (delta_y > 0)
        {
            pImageManager->ZoomIn();
        }
        else
        {
            pImageManager->ZoomOut();
        }
        pEvent->accept();
    }
    else
    {
        pEvent->ignore();
    }
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
