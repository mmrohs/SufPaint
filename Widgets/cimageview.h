#ifndef CIMAGEVIEW_H
#define CIMAGEVIEW_H

#include <QWidget>
#include "../Misc/cimageviewtransform.h"
#include "../Misc/cpixelgrid.h"
#include "../Misc/cbackgroundpattern.h"


/* Widget for displaying a QImage items
*/
class CImageView : public QWidget
{
    Q_OBJECT
public:
    explicit CImageView(QWidget* pParent);

    qreal GetScale() const;
    qreal GetZoom() const;
    void ResetZoom();
    // zoom in/out without fixed image point
    void ZoomIn();
    void ZoomOut();
    // zoom in/out using a fixed image point
    void ZoomIn(QPoint fixedPos);
    void ZoomOut(QPoint fixedPos);
    // move the view
    void MoveView(QPoint distance);

    QPoint GetCenter() const;

    const CImageViewTransform* GetTransformation() const;

Q_SIGNALS:
    void ViewChanged();

public slots:
    void ImagePixelsChanged();
    void ImagePropertiesChanged();

protected:
    virtual void resizeEvent(QResizeEvent* pEvent) override;
    virtual void paintEvent(QPaintEvent* pEvent) override;
    virtual void wheelEvent(QWheelEvent* pEvent) override;
    virtual void mousePressEvent(QMouseEvent* pEvent) override;
    virtual void mouseReleaseEvent(QMouseEvent* pEvent) override;
    virtual void mouseMoveEvent(QMouseEvent* pEvent) override;

private:
    class CTool* GetActiveTool();

    QBrush GetBackgroundBrush() const;

private:
    CImageViewTransform m_trafo;
    CPixelGrid m_pixelgrid;
    CBackgroundPattern m_background;
};

#endif // CIMAGEVIEW_H
