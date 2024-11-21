#ifndef CSCALE_H
#define CSCALE_H

#include <QObject>
#include <QRect>


/* Scaling / zooming class
*/
class CScale
{
public:
    CScale();

    void SetScale(qreal scale);
    qreal GetScale() const;
    qreal GetOldScale() const;
    qreal GetScaleDivByOldScale() const;

    void AutoScale(QRect imageRect, QRect widgetRect);
    void ResetScale();
    bool SwitchToNextScale();
    bool SwitchToPrevScale();

private:
    qreal FindNextPrevScale(qreal oldScale, bool bNext) const;

private:
    // scaling / zoom factor [0.1 - 10.0]
    qreal m_scale;
    qreal m_oldScale;
};

#endif // CSCALE_H
