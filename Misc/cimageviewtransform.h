#ifndef CIMAGEVIEWTRANSFORM_H
#define CIMAGEVIEWTRANSFORM_H

#include <QPoint>
#include <qsize.h>


/* Handles the view information of CImageView
*/
class CImageViewTransform
{
public:
    explicit CImageViewTransform(class CImageView*);

    // zoom in/out with image center as fixed point
    void ZoomIn();
    void ZoomOut();

    // zoom in/out with a variable fixed point (-> mouse position)
    void ZoomIn(QPoint fixedPoint);
    void ZoomOut(QPoint fixedPoint);

    // Update the coordinate system
    void Update();

    // returns the top-left coordinate of the image
    QPoint GetImageOrigin() const;

    // image scaling
    qreal GetScale() const;

    // reset to autoscale
    void Reset();

    // coordinate transformations between image and widget
    QPoint TransformWidgetToImage(QPoint widgetPos) const;
    QPoint TransformImageToWidget(QPoint imagePos) const;

private:
    // scaling related functions
    void AutoScale();
    void ResetScale();
    void SetScale(qreal scale);
    void SwitchToNextScale();
    void SwitchToPrevScale();
    qreal FindNextPrevScale(qreal oldScale, bool bNext) const;

    // calculates the image origin
    void CalcImageOrigin();

    // calculates the fixed point for central zooming
    void CalcFixedPoint();

    // set the fixed point for zooming
    void SetFixedPoint(QPoint fixedPoint);

    QSize GetImageSize() const;

    // offset related functions
    void CalcImageOffset();
    void CalcImageOffset(QPoint fixedPoint);

    // Check if the given point is inside the image rect
    QPoint CheckPointInImage(QPoint pos);

private:
    class CImageView* m_pImageView;

    // Position of the top-left corner of the image in widget coordinate system
    QPoint m_imageOrigin;

    // scaling / zoom factor [0.1 - 10.0]
    qreal m_scale;
    qreal m_oldScale;

    // fixed coordinate for zoom operations
    // (= widget center for zoom via menu, otherwise mouse position)
    QPoint m_fixedPoint;

    // Vector from fixed point to image origin
    QPoint m_offset;
};

#endif // CIMAGEVIEWTRANSFORM_H
