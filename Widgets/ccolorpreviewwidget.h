#ifndef CCOLORPREVIEWWIDGET_H
#define CCOLORPREVIEWWIDGET_H

#include <QWidget>


/* Widget displays the selected foreground and background color
 */
class CColorPreviewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CColorPreviewWidget(QWidget *parent = nullptr);

public slots:
    void ColorChanged();

protected:
    virtual void paintEvent(QPaintEvent* pEvent) override;
    virtual void mousePressEvent(QMouseEvent* pEvent) override;

private:
    void DrawColorRect(QRect rect, QColor color);

private:
    QColor m_foregroundColor;
    QColor m_backgroundColor;
    QRect  m_rectFB; // union of both color rectangles (background and foreground)
};

#endif // CCOLORPREVIEWWIDGET_H
