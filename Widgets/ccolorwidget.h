#ifndef CCOLORWIDGET_H
#define CCOLORWIDGET_H

#include <QGroupBox>

class CColorWidget : public QGroupBox
{
public:
    explicit CColorWidget(QWidget* pParent);

public slots:
    void ColorPicked(QColor color);

protected:
    virtual void paintEvent(QPaintEvent* pEvent) override;

private:
    QColor m_selectedColor;
};

#endif // CCOLORWIDGET_H
