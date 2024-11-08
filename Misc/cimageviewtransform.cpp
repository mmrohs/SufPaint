#include "cimageviewtransform.h"
#include <QSize>
#include "../Widgets/cimageview.h"
#include "../Management/cimagemanager.h"

// small gap between image and widget border
#define GAP 10


CImageViewTransform::CImageViewTransform(class CImageView* pImageView)
    : m_pImageView(pImageView), m_scale(1.0), m_oldScale(1.0)
{
    Update();
}

void CImageViewTransform::ZoomIn()
{
    SwitchToNextScale();
    CalcImageOffset();
    CalcFixedPoint();
    CalcImageOrigin();
}

void CImageViewTransform::ZoomOut()
{
    SwitchToPrevScale();
    CalcImageOffset();
    CalcFixedPoint();
    CalcImageOrigin();
}

void CImageViewTransform::ZoomIn(QPoint fixedPoint)
{
    QPoint pos = CheckPointInImage(fixedPoint);
    CalcImageOffset(pos);
    SwitchToNextScale();
    SetFixedPoint(pos);
    CalcImageOrigin();
}

void CImageViewTransform::ZoomOut(QPoint fixedPoint)
{
    QPoint pos = CheckPointInImage(fixedPoint);
    CalcImageOffset(pos);
    SwitchToPrevScale();
    SetFixedPoint(pos);
    CalcImageOrigin();
}

void CImageViewTransform::Update()
{
    CalcImageOffset();
    CalcFixedPoint();
    CalcImageOrigin();
}

QPoint CImageViewTransform::GetImageOrigin() const
{
    return m_imageOrigin / m_scale;
}

void CImageViewTransform::CalcImageOrigin()
{
    qreal x = m_fixedPoint.x() + (m_scale / m_oldScale) * m_offset.x();
    qreal y = m_fixedPoint.y() + (m_scale / m_oldScale) * m_offset.y();
    m_imageOrigin = QPoint(x, y);
}

void CImageViewTransform::CalcFixedPoint()
{
    QSize widgetSize = m_pImageView->size();
    qreal x = 0.5 * widgetSize.width();
    qreal y = 0.5 * widgetSize.height();
    m_fixedPoint = QPoint(x, y);
}

void CImageViewTransform::SetFixedPoint(QPoint fixedPoint)
{
    m_fixedPoint = fixedPoint;
}

void CImageViewTransform::CalcImageOffset()
{
    QSize imgSize = GetImageSize();
    m_offset = QPoint(-0.5 * imgSize.width(), -0.5 * imgSize.height());
}

void CImageViewTransform::CalcImageOffset(QPoint fixedPoint)
{
    m_oldScale = GetScale();
    m_offset = m_imageOrigin - fixedPoint;
}

QSize CImageViewTransform::GetImageSize() const
{
    return CImageManager::GetImageManager()->GetImageSize();
}

QPoint CImageViewTransform::CheckPointInImage(QPoint pos)
{
    int x = pos.x();
    int y = pos.y();

    // position has to be inside the image, so move it if necessary
    QPointF posImgOrig = GetImageOrigin();
    QSize imgSize = GetImageSize();
    if (x < posImgOrig.x())
        x = posImgOrig.x();
    if (x > posImgOrig.x() + imgSize.width())
        x = posImgOrig.x() + imgSize.width();
    if (y < posImgOrig.y())
        y = posImgOrig.y();
    if (y > posImgOrig.y() + imgSize.height())
        y = posImgOrig.y() + imgSize.height();

    return QPoint(x, y);
}

QPoint CImageViewTransform::TransformWidgetToImage(QPoint widgetPos) const
{
    QPointF pointF(widgetPos);
    pointF = (pointF - m_scale * GetImageOrigin()) / m_scale;
    return QPoint(pointF.x(), pointF.y());
}

QPoint CImageViewTransform::TransformImageToWidget(QPoint imagePos) const
{
    QPointF pointF(imagePos);
    pointF = pointF * m_scale + m_scale * GetImageOrigin();
    return QPoint(pointF.x(), pointF.y());
}

qreal CImageViewTransform::GetScale() const
{
    return m_scale;
}

void CImageViewTransform::SetScale(qreal scale)
{
    m_scale = scale;
}

/* scales the image to ideally fit the widget size + a little gap
*/
void CImageViewTransform::AutoScale()
{
    qreal factor = 1.0;
    CImageManager* pImageManager = CImageManager::GetImageManager();
    if (pImageManager->HasImage())
    {
        QRect wRect = m_pImageView->rect();
        QRect iRect = pImageManager->GetImageRect();
        if (iRect.height() > wRect.height())
        {
            factor *= wRect.height() / qreal(iRect.height() + GAP);
        }
        if (factor * iRect.width() > wRect.width())
        {
            factor *= wRect.width() / qreal(factor * iRect.width() + GAP);
        }
    }
    SetScale(factor);
}

void CImageViewTransform::SwitchToNextScale()
{
    qreal oldScale = GetScale();
    qreal newScale = FindNextPrevScale(oldScale, true);
    if (newScale != oldScale)
    {
        SetScale(newScale);
    }
}

void CImageViewTransform::SwitchToPrevScale()
{
    qreal oldScale = GetScale();
    qreal newScale = FindNextPrevScale(oldScale, false);
    if (newScale != oldScale)
    {
        SetScale(newScale);
    }
}

/* reset the scaling to 100%
*/
void CImageViewTransform::ResetScale()
{
    SetScale(1.0);
    m_oldScale = 1.0;
}

void CImageViewTransform::Reset()
{
    ResetScale();
    CalcImageOffset();
    CalcFixedPoint();
    CalcImageOrigin();
}

qreal CImageViewTransform::FindNextPrevScale(qreal oldScale, bool bNext) const
{
    // possible scale values (resulting zoom: 10% to 1000%)
    static const std::vector<qreal> vecScales =
        { 0.1, 0.17, 0.25, 0.5, 0.66, 0.75, 1.0, 1.25, 1.5, 1.75, 2.0, 2.5, 3.0, 4.0, 5.0, 7.5, 10.0 };

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
