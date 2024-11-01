#include "cimageview.h"
#include <QPainter>
#include <QPaintEvent>
#include "../Management/cimagemanager.h"
#include "../Management/ctoolmanager.h"
#include "../Tools/ctool.h"


CImageView::CImageView(QWidget* pParent)
    : QWidget(pParent),
    m_pImage(NULL)
{
}

void CImageView::SetImage(QImage* pImage)
{
    m_pImage = pImage;
    AutoScale();
    emit imageChanged(m_pImage != NULL);
}

qreal CImageView::GetScale() const
{
    return m_scale;
}

void CImageView::SetScale(qreal scale)
{
    m_scale = scale;
    update();
    emit scaleChanged();
}

/* reset the scaling to 100%
*/
void CImageView::ResetScale()
{
    SetScale(1.0);
}

void CImageView::SetNextScale()
{
    qreal oldScale = GetScale();
    qreal newScale = FindNextPrevScale(oldScale, true);
    if (newScale != oldScale)
    {
        SetScale(newScale);
    }
}

void CImageView::SetPrevScale()
{
    qreal oldScale = GetScale();
    qreal newScale = FindNextPrevScale(oldScale, false);
    if (newScale != oldScale)
    {
        SetScale(newScale);
    }
}

void CImageView::AutoScale()
{
    qreal factor = 1.0;
    if (m_pImage != NULL)
    {
        static const int gap = 10;
        QRect wRect = this->rect();
        QRect iRect = m_pImage->rect();
        if (iRect.height() > wRect.height())
        {
            factor *= wRect.height() / qreal(iRect.height() + gap);
        }
        if (factor * iRect.width() > wRect.width())
        {
            factor *= wRect.width() / qreal(factor * iRect.width() + gap);
        }
    }
    SetScale(factor);
}

qreal CImageView::FindNextPrevScale(qreal oldScale, bool bNext) const
{
    // possible scale values (resulting zoom: 10% to 1000%)
    static const std::vector<qreal> vecScales =
        { 0.1, 0.17, 0.25, 0.5, 0.75, 1.0, 1.5, 2.0, 4.0, 5.0, 7.5, 10.0 };

    for (int i = 0; i < vecScales.size(); i++)
    {
        qreal scale_i = vecScales[i];
        qreal scale_p = (i > 0) ? vecScales[i - 1] : scale_i;
        qreal scale_n = (i + 1 < vecScales.size()) ? vecScales[i + 1] : scale_i;

        if (abs(scale_i - oldScale) < 1E-10) // exact match
        {
            return bNext ? scale_n : scale_p;
        }
        else if (bNext && scale_i < oldScale && oldScale < scale_n)
        {
            return scale_n;
        }
        else if (!bNext && scale_p < oldScale && oldScale < scale_i)
        {
            return scale_p;
        }
        else if (oldScale < scale_p)
        {
            return scale_p;
        }
    }
    return oldScale;
}

QPoint CImageView::TransformWidgetPosToImagePos(QPoint widgetPos)
{
    QPointF pointF(widgetPos);
    pointF = (pointF - m_scale * GetImageOrigin()) / m_scale;
    return QPoint(pointF.x(), pointF.y());
}

QPoint CImageView::TransformImagePosToWidgetPos(QPoint imagePos)
{
    QPointF pointF(imagePos);
    pointF = pointF * m_scale + m_scale * GetImageOrigin();
    return QPoint(pointF.x(), pointF.y());
}

QPointF CImageView::GetImageOrigin() const
{
    QSize wSize = this->size();
    QSize iSize = m_pImage->size();
    qreal x = 0.5 * wSize.width() / m_scale - 0.5 * iSize.width();
    qreal y = 0.5 * wSize.height() / m_scale - 0.5 * iSize.height();
    return QPointF(x, y);
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
        paint.scale(m_scale, m_scale);
        paint.drawImage(GetImageOrigin(), *m_pImage);
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
        QPoint imagePos = TransformWidgetPosToImagePos(widgetPos);
        pTool->ProcessMousePressEvent(imagePos, pEvent);
        pEvent->accept();
    }
    else
    {
        pEvent->ignore();
    }
}
