#ifndef CCOLORHISTORYWIDGET_H
#define CCOLORHISTORYWIDGET_H

#include <QWidget>

// number of historical colors
#define NCOLORS 9


/* Displays the previously used colors
 * And allows selection of these colors
*/
class CColorHistoryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CColorHistoryWidget(QWidget *parent = nullptr);

    void AddColorToHistory(QColor);

Q_SIGNALS:
    void ColorPicked(QColor);

protected:
    virtual void paintEvent(QPaintEvent* pEvent) override;
    virtual void mousePressEvent(QMouseEvent* pEvent) override;

private:
    void ResetColors();
    void ShiftColors();
    void SetRects();

private:
    QColor m_colors[NCOLORS];
    QRect  m_colorRects[NCOLORS];
};

#endif // CCOLORHISTORYWIDGET_H
