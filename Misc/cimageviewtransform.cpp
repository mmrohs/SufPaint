#include "cimageviewtransform.h"
#include <QSize>
#include "../Widgets/cimageview.h"
#include "../Management/cimagemanager.h"


CImageViewTransform::CImageViewTransform(class CImageView* pImageView)
    : m_pImageView(pImageView)
{
    Reset();
}

void CImageViewTransform::ZoomIn()
{
    ZoomIn(GetWidgetCenter());
}

void CImageViewTransform::ZoomOut()
{
    ZoomOut(GetWidgetCenter());
}

void CImageViewTransform::ZoomIn(QPoint fixedPoint)
{
    SetFixedPoint(fixedPoint);
    if (m_scale.SwitchToNextScale())
        CalcImageOrigin();
}

void CImageViewTransform::ZoomOut(QPoint fixedPoint)
{
    SetFixedPoint(fixedPoint);
    if (m_scale.SwitchToPrevScale())
        CalcImageOrigin();
}

void CImageViewTransform::CalcImageOrigin()
{
    QPoint offset = GetImageOffset();
    qreal scaleDivByOldScale = m_scale.GetScaleDivByOldScale();
    qreal x = m_fixedPoint.x() + scaleDivByOldScale * offset.x();
    qreal y = m_fixedPoint.y() + scaleDivByOldScale * offset.y();
    m_imageOrigin = QPoint(x, y);
}

void CImageViewTransform::SetFixedPoint(QPoint fixedPoint)
{
    m_fixedPoint = CheckPositionInImage(fixedPoint);
}

QPoint CImageViewTransform::GetImageOffset()
{
    if (m_imageOrigin.isNull())
    {
        QSize imgSize = GetImageSize();
        m_imageOrigin = m_fixedPoint - 0.5 * QPoint(imgSize.width(), imgSize.height());
    }
    return m_imageOrigin - m_fixedPoint;
}

qreal CImageViewTransform::GetScale() const
{
    return m_scale.GetScale();
}

QPoint CImageViewTransform::GetImageOrigin() const
{
    return m_imageOrigin;
}

QPoint CImageViewTransform::GetImageOriginScaled() const
{
    return m_imageOrigin / GetScale();
}

QSize CImageViewTransform::GetImageSize() const
{
    return CImageManager::GetImageManager()->GetImageSize();
}

QSize CImageViewTransform::GetImageSizeScaled() const
{
    return GetImageSize() * GetScale();
}

QPoint CImageViewTransform::GetWidgetCenter() const
{
    return m_pImageView->GetCenter();
}

QPoint CImageViewTransform::CheckPositionInImage(QPoint pos)
{
    int x = pos.x();
    int y = pos.y();

    // position has to be inside the image, so move it if necessary
    QPointF posImgOrig = GetImageOrigin();
    QSize imgSize = GetImageSizeScaled();
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
    pointF = (pointF / GetScale()) - GetImageOriginScaled();
    return QPoint(pointF.x(), pointF.y());
}

QPoint CImageViewTransform::TransformImageToWidget(QPoint imagePos) const
{
    QPointF pointF(imagePos);
    pointF = GetScale() * (pointF + GetImageOriginScaled());
    return QPoint(pointF.x(), pointF.y());
}

void CImageViewTransform::Reset()
{
    m_scale.ResetScale();
    m_imageOrigin = QPoint();
    SetFixedPoint(GetWidgetCenter());
    CalcImageOrigin();
}

void CImageViewTransform::Update()
{
    m_scale.ResetScale();
    SetFixedPoint(GetWidgetCenter());
    CalcImageOrigin();
}

