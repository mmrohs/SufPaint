#include "cimageviewtransform.h"
#include <QSize>
#include "../Widgets/cimageview.h"
#include "../Management/cimagemanager.h"

// small gap between image and widget border
#define GAP 10


CImageViewTransform::CImageViewTransform(class CImageView* pImageView)
    : m_pImageView(pImageView), m_scale(1.0)
{
}

QPointF CImageViewTransform::GetImageOrigin() const
{
    QSize wSize = m_pImageView->size();
    QSize iSize = CImageManager::GetImageManager()->GetImageSize();
    qreal x = 0.5 * wSize.width() / m_scale - 0.5 * iSize.width();
    qreal y = 0.5 * wSize.height() / m_scale - 0.5 * iSize.height();
    return QPointF(x, y);
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

/* reset the scaling to 100%
*/
void CImageViewTransform::ResetScale()
{
    SetScale(1.0);
}

void CImageViewTransform::SetNextScale()
{
    qreal oldScale = GetScale();
    qreal newScale = FindNextPrevScale(oldScale, true);
    if (newScale != oldScale)
    {
        SetScale(newScale);
    }
}

void CImageViewTransform::SetPrevScale()
{
    qreal oldScale = GetScale();
    qreal newScale = FindNextPrevScale(oldScale, false);
    if (newScale != oldScale)
    {
        SetScale(newScale);
    }
}

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

qreal CImageViewTransform::FindNextPrevScale(qreal oldScale, bool bNext) const
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
