#ifndef CCOLORWIDGET_H
#define CCOLORWIDGET_H

#include <QGroupBox>

class CColorWidget : public QGroupBox
{
    Q_OBJECT
public:
    explicit CColorWidget(QWidget* pParent);

public slots:
    void ColorPicked(QColor color);

protected:
    virtual void paintEvent(QPaintEvent* pEvent) override;
    virtual void mousePressEvent(QMouseEvent* pEvent) override;

private:
    void AddLayout();
    void AddConnections();

    void CheckRgbaValues();
    void DrawColorRect(QRect rect, QColor color);

private slots:
    void RgbaChanged();

private:
    class QSpinBox* m_pSpinBoxes[4]; // [0]: Red, [1]: Green, [2]: Blue, [3]: Alpha

    QColor m_foregroundColor;
    QColor m_backgroundColor;

    QRect m_rectFB; // union of both color rects (background and foreground)
};

#endif // CCOLORWIDGET_H
