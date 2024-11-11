#include "cimageviewtransform.h"
#include <QSize>
#include "../Widgets/cimageview.h"
#include "../Management/cimagemanager.h"


CImageViewTransform::CImageViewTransform(class CImageView* pImageView)
    : m_pImageView(pImageView)
{
    Update();
}

void CImageViewTransform::ZoomIn()
{
    m_scale.SwitchToNextScale();
    CalcImageOffset();
    CalcFixedPoint();
    CalcImageOrigin();
}

void CImageViewTransform::ZoomOut()
{
    m_scale.SwitchToPrevScale();
    CalcImageOffset();
    CalcFixedPoint();
    CalcImageOrigin();
}

void CImageViewTransform::ZoomIn(QPoint fixedPoint)
{
    QPoint pos = CheckPointInImage(fixedPoint);
    CalcImageOffset(pos);
    m_scale.SwitchToNextScale();
    SetFixedPoint(pos);
    CalcImageOrigin();
}

void CImageViewTransform::ZoomOut(QPoint fixedPoint)
{
    QPoint pos = CheckPointInImage(fixedPoint);
    CalcImageOffset(pos);
    m_scale.SwitchToPrevScale();
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
    return m_imageOrigin / GetScale();
}

void CImageViewTransform::CalcImageOrigin()
{
    qreal scaleDivByOldScale = m_scale.GetScaleDivByOldScale();
    qreal x = m_fixedPoint.x() + scaleDivByOldScale * m_offset.x();
    qreal y = m_fixedPoint.y() + scaleDivByOldScale * m_offset.y();
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
    m_offset = m_imageOrigin - fixedPoint;
}

qreal CImageViewTransform::GetScale() const
{
    return m_scale.GetScale();
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
    pointF = (pointF / m_scale.GetScale()) - GetImageOrigin();
    return QPoint(pointF.x(), pointF.y());
}

QPoint CImageViewTransform::TransformImageToWidget(QPoint imagePos) const
{
    QPointF pointF(imagePos);
    pointF = m_scale.GetScale() * (pointF + GetImageOrigin());
    return QPoint(pointF.x(), pointF.y());
}

void CImageViewTransform::Reset()
{
    m_scale.ResetScale();
    CalcImageOffset();
    CalcFixedPoint();
    CalcImageOrigin();
}

