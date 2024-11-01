#ifndef CCOLORPALETTEWIDGET_H
#define CCOLORPALETTEWIDGET_H

#include <QWidget>


class CColorPaletteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CColorPaletteWidget(QWidget *parent = nullptr);
    ~CColorPaletteWidget();

public slots:
    void ColorChanged();

protected:
    virtual void paintEvent(QPaintEvent* pEvent) override;
    virtual void mousePressEvent(QMouseEvent* pEvent) override;
    virtual void mouseMoveEvent(QMouseEvent* pEvent) override;

private:
    QSize   GetPatternSize() const;
    QImage* GetPatternImage();

private:
    class CColorPatternImage* m_pImage;
    QColor m_color;
    QPoint m_selPoint;  // selected point in the pattern image
};

#endif // CCOLORPALETTEWIDGET_H
