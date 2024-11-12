#include "cimageview.h"
#include <QPainter>
#include <QPaintEvent>
#include "../Management/cimagemanager.h"
#include "../Management/cselectionmanager.h"
#include "../Management/ctoolmanager.h"
#include "../Tools/ctool.h"


CImageView::CImageView(QWidget* pParent)
    : QWidget(pParent),
    m_trafo(this)
{
}

qreal CImageView::GetScale() const
{
    return m_trafo.GetScale();
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

const CImageViewTransform* CImageView::GetTransformation() const
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

QBrush CImageView::GetBackgroundBrush() const
{
    static const QBrush backgroundBrush = QBrush(QColor(120, 120, 120));
    return backgroundBrush;
}

/*virtual*/ void CImageView::resizeEvent(QResizeEvent* pEvent)
{
    QWidget::resizeEvent(pEvent);
    m_trafo.Update();
    update();
}

/*virtual*/ void CImageView::paintEvent(QPaintEvent* pEvent)
{
    QPainter paint;
    paint.begin(this);
    paint.setClipRect(pEvent->rect());
    paint.fillRect(pEvent->rect(), GetBackgroundBrush());

    // draw image if available
    CImageManager* pImageManager = CImageManager::GetImageManager();
    if (pImageManager->HasImage())
    {
        QPointF pos = m_trafo.GetImageOriginScaled();
        qreal scale = m_trafo.GetScale();
        paint.scale(scale, scale);
        paint.drawImage(pos, *pImageManager->GetImage());
    }

    // draw selection if available
    CSelectionManager* pSelectionManager = CSelectionManager::GetSelectionManager();
    if (pSelectionManager->HasSelection())
    {
        CSelection* pSelection = pSelectionManager->GetSelection();
        pSelection->Paint(paint);
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
    if (pTool != NULL && pEvent->button() == Qt::LeftButton)
    {
        pTool->ProcessMousePressEvent(pEvent);
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
    if (pTool != NULL && pEvent->button() == Qt::LeftButton)
    {
        pTool->ProcessMouseReleaseEvent(pEvent);
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
        pTool->ProcessMouseMoveEvent(pEvent);
        pEvent->accept();
    }
    else
    {
        pEvent->ignore();
    }
}
