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

    void SetImage(QImage* pImage);

    qreal GetZoom() const;
    void ZoomIn();
    void ZoomOut();
    void ResetZoom();

    const CImageViewTransform* GetTrafo() const;

Q_SIGNALS:
    void imageChanged();
    void scaleChanged();

protected:
    virtual void paintEvent(QPaintEvent* pEvent) override;
    virtual void wheelEvent(QWheelEvent* pEvent) override;
    virtual void mousePressEvent(QMouseEvent* pEvent) override;
    virtual void mouseReleaseEvent(QMouseEvent* pEvent) override;
    virtual void mouseMoveEvent(QMouseEvent* pEvent) override;

private:
    class CTool* GetActiveTool();

private:
    CImageViewTransform m_trafo;
    // todo: remove
    QImage* m_pImage;
};

#endif // CIMAGEVIEW_H
