#ifndef CIMAGEVIEWTRANSFORM_H
#define CIMAGEVIEWTRANSFORM_H

#include <QPoint>


/* Handles the view information of CImageView
*/
class CImageViewTransform
{
public:
    explicit CImageViewTransform(class CImageView*);

    QPointF GetImageOrigin() const;

    // image scaling
    qreal GetScale() const;
    void AutoScale();
    void ResetScale();
    void SetNextScale();
    void SetPrevScale();

    // coordinate transformations
    QPoint TransformWidgetToImage(QPoint widgetPos) const;
    QPoint TransformImageToWidget(QPoint imagePos) const;

private:
    void SetScale(qreal scale);
    qreal FindNextPrevScale(qreal oldScale, bool bNext) const;

private:
    class CImageView* m_pImageView;
    qreal m_scale;
};

#endif // CIMAGEVIEWTRANSFORM_H
