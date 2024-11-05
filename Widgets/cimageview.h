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
    bool HasImage() const;
    QSize GetImageSize() const;
    QRect GetImageRect() const;

    void ZoomIn();
    void ZoomOut();
    void ResetZoom();

    const CImageViewTransform* GetTrafo() const;

protected:
    virtual void paintEvent(QPaintEvent* pEvent) override;
    virtual void wheelEvent(QWheelEvent* pEvent) override;
    virtual void mousePressEvent(QMouseEvent* pEvent) override;
    virtual void mouseReleaseEvent(QMouseEvent* pEvent) override;
    virtual void mouseMoveEvent(QMouseEvent* pEvent) override;

Q_SIGNALS:
    void imageChanged(bool);
    void scaleChanged();

private:
    class CTool* GetActiveTool();

private:
    CImageViewTransform m_trafo;
    QImage* m_pImage;
};

#endif // CIMAGEVIEW_H
