#ifndef CCOLORPALETTEWIDGET_H
#define CCOLORPALETTEWIDGET_H

#include <QWidget>


class CColorPaletteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CColorPaletteWidget(QWidget *parent = nullptr);
    ~CColorPaletteWidget();

Q_SIGNALS:
    void ColorPicked(QColor);

protected:
    virtual void paintEvent(QPaintEvent* pEvent) override;
    virtual void mousePressEvent(QMouseEvent* pEvent) override;
    virtual void mouseMoveEvent(QMouseEvent* pEvent) override;

private:
    QSize   GetPatternSize() const;
    QImage* GetPatternImage();

private:
    class CColorPatternImage* m_pImage;
    QPoint  m_selPoint;  // selected point in the pattern image
};

#endif // CCOLORPALETTEWIDGET_H
