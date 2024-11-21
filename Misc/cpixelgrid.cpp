#include "cscale.h"

// small gap between image and widget border
#define GAP 10


CScale::CScale()
    : m_scale(1.0), m_oldScale(1.0)
{
}

void CScale::SetScale(qreal scale)
{
    m_oldScale = m_scale;
    m_scale = scale;
}

qreal CScale::GetScale() const
{
    return m_scale;
}

qreal CScale::GetOldScale() const
{
    return m_oldScale;
}

qreal CScale::GetScaleDivByOldScale() const
{
    return m_scale / m_oldScale;
}

bool CScale::SwitchToNextScale()
{
    qreal oldScale = GetScale();
    qreal newScale = FindNextPrevScale(oldScale, true);
    if (newScale != oldScale)
    {
        SetScale(newScale);
        return true;
    }
    return false;
}

bool CScale::SwitchToPrevScale()
{
    qreal oldScale = GetScale();
    qreal newScale = FindNextPrevScale(oldScale, false);
    if (newScale != oldScale)
    {
        SetScale(newScale);
        return true;
    }
    return false;
}

/* reset the scaling to 100%
*/
void CScale::ResetScale()
{
    SetScale(1.0);
    m_oldScale = 1.0;
}

/* scales the image to ideally fit the widget size + a little gap
*/
void CScale::AutoScale(QRect imageRect, QRect widgetRect)
{
    qreal factor = 1.0;
    if (imageRect.height() > widgetRect.height())
    {
        factor *= widgetRect.height() / qreal(imageRect.height() + GAP);
    }
    if (factor * imageRect.width() > widgetRect.width())
    {
        factor *= widgetRect.width() / qreal(factor * imageRect.width() + GAP);
    }
    SetScale(factor);
}

qreal CScale::FindNextPrevScale(qreal oldScale, bool bNext) const
{
    // possible scale values (resulting zoom: 10% to 1000%)
    static const std::vector<qreal> vecScales =
        { 0.1, 0.17, 0.25, 0.5, 0.66, 0.75, 1.0, 1.25, 1.5, 1.75, 2.0, 2.5, 3.0, 4.0, 5.0, 7.5, 10.0,
          12.5, 15.0, 17.5, 20.0, 25.0, 30.0, 40.0, 50.0 };

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
