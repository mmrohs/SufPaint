#ifndef CIMAGEVIEW_H
#define CIMAGEVIEW_H

#include <QWidget>

// Widget for displaying a QImage item
class CImageView : public QWidget
{
    Q_OBJECT
public:
    explicit CImageView(QWidget* pParent);

    void SetImage(QImage* pImage);

    qreal GetScale() const;
    void ResetScale();
    void SetNextScale();
    void SetPrevScale();

    QPoint TransformWidgetPosToImagePos(QPoint widgetPos);
    QPoint TransformImagePosToWidgetPos(QPoint imagePos);

protected:
    virtual void paintEvent(QPaintEvent* pEvent) override;
    virtual void wheelEvent(QWheelEvent* pEvent) override;
    virtual void mousePressEvent(QMouseEvent* pEvent) override;

Q_SIGNALS:
    void imageChanged(bool);
    void scaleChanged();

private:
    void AutoScale();
    void SetScale(qreal scale);
    qreal FindNextPrevScale(qreal oldScale, bool bNext) const;

    QPointF GetImageOrigin() const;

    class CTool* GetActiveTool();

private:
    QImage* m_pImage;
    qreal   m_scale = 1.0;
};

#endif // CIMAGEVIEW_H
