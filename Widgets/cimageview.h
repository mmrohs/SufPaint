#ifndef CIMAGEVIEW_H
#define CIMAGEVIEW_H

#include <QWidget>
#include "../Misc/cimageviewtransform.h"


/* Widget for displaying a QImage items
*/
class CImageView : public QWidget
{
    Q_OBJECT
public:
    explicit CImageView(QWidget* pParent);

    qreal GetZoom() const;
    void ResetZoom();
    // zoom in/out without fixed image point
    void ZoomIn();
    void ZoomOut();
    // zoom in/out using a fixed image point
    void ZoomIn(QPoint fixedPos);
    void ZoomOut(QPoint fixedPos);

    QPoint GetCenter() const;

    const CImageViewTransform* GetTrafo() const;

Q_SIGNALS:
    void ViewChanged();

public slots:
    void ImageChanged();

protected:
    virtual void resizeEvent(QResizeEvent* pEvent) override;
    virtual void paintEvent(QPaintEvent* pEvent) override;
    virtual void wheelEvent(QWheelEvent* pEvent) override;
    virtual void mousePressEvent(QMouseEvent* pEvent) override;
    virtual void mouseReleaseEvent(QMouseEvent* pEvent) override;
    virtual void mouseMoveEvent(QMouseEvent* pEvent) override;

private:
    class CTool* GetActiveTool();

private:
    CImageViewTransform m_trafo;
};

#endif // CIMAGEVIEW_H
