#ifndef CIMAGEVIEWTRANSFORM_H
#define CIMAGEVIEWTRANSFORM_H

#include <QPoint>
#include <qsize.h>
#include "cscale.h"


/* Handles the view transformations of CImageView
*/
class CImageViewTransform
{
public:
    explicit CImageViewTransform(class CImageView*);

    // zoom in/out with widget center as fixed point
    void ZoomIn();
    void ZoomOut();

    // zoom in/out with a variable fixed point (-> mouse position)
    void ZoomIn(QPoint fixedPoint);
    void ZoomOut(QPoint fixedPoint);

    // returns the top-left coordinate of the image
    QPoint GetImageOrigin() const;
    QPoint GetImageOriginScaled() const;

    // returns the image scaling factor
    qreal GetScale() const;

    // reset to original view
    void Reset();

    // update the coordinate system
    void Update();

    // coordinate transformations between image and widget coordinate systems
    QPoint TransformWidgetToImage(QPoint widgetPos) const;
    QPoint TransformImageToWidget(QPoint imagePos) const;

private:
    // calculates the image origin
    void CalcImageOrigin();

    // set the fixed point for zooming
    void SetFixedPoint(QPoint fixedPoint);

    // return the image size
    QSize GetImageSize() const;
    QSize GetImageSizeScaled() const;

    // return the widget center coordinate
    QPoint GetWidgetCenter() const;

    // returns the vector from 'm_fixedPoint' to 'm_imageOrigin'
    QPoint GetImageOffset();

    // Check if the given position is inside the image rect
    // if it's not, then it gets moved into the image
    QPoint CheckPositionInImage(QPoint pos);

private:
    class CImageView* m_pImageView;

    // top-left corner of the image in the widget coordinate system
    QPoint m_imageOrigin;

    // fixed coordinate for zoom operations
    // (= widget center for zoom via menu, otherwise mouse position)
    QPoint m_fixedPoint;

    // scaling / zoom factor [0.1 - 10.0]
    CScale m_scale;
};

#endif // CIMAGEVIEWTRANSFORM_H
