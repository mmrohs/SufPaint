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
    m_trafo.ZoomIn();
    emit ViewChanged();
    update();
}

void CImageView::ZoomIn(QPoint fixedPos)
{
    m_trafo.ZoomIn(fixedPos);
    emit ViewChanged();
    update();
}

void CImageView::ZoomOut()
{
    m_trafo.ZoomOut();
    emit ViewChanged();
    update();
}

void CImageView::ZoomOut(QPoint fixedPos)
{
    m_trafo.ZoomOut(fixedPos);
    emit ViewChanged();
    update();
}

void CImageView::ResetZoom()
{
    m_trafo.Reset();
    emit ViewChanged();
    update();
}

QPoint CImageView::GetCenter() const
{
    qreal x = 0.5 * size().width();
    qreal y = 0.5 * size().height();
    return QPoint(x, y);
}

const CImageViewTransform* CImageView::GetTrafo() const
{
    return &m_trafo;
}

void CImageView::ImageChanged()
{
    m_trafo.Update();
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

/*virtual*/ void CImageView::resizeEvent(QResizeEvent* pEvent)
{
    QWidget::resizeEvent(pEvent);
    m_trafo.Update();
    update();
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
        QPointF pos = m_trafo.GetImageOriginScaled();
        qreal scale = m_trafo.GetScale();
        paint.scale(scale, scale);
        paint.drawImage(pos, *pImageManager->GetImage());
    }
    paint.end();
}

/*virtual*/ void CImageView::wheelEvent(QWheelEvent* pEvent)
{
    QPoint widgetPos (pEvent->position().x(), pEvent->position().y());
    int delta_y = pEvent->angleDelta().y();
    if (delta_y > 0)
    {
        ZoomIn(widgetPos);
    }
    else
    {
        ZoomOut(widgetPos);
    }
    pEvent->accept();
}

/*virtual*/ void CImageView::mousePressEvent(QMouseEvent* pEvent)
{
    CTool* pTool = GetActiveTool();
    if (pTool != NULL)
    {
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
        pTool->ProcessMouseMoveEvent(pEvent, this);
        pEvent->accept();
    }
    else
    {
        pEvent->ignore();
    }
}
