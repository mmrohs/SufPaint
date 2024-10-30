#ifndef CCOLORRGBAWIDGET_H
#define CCOLORRGBAWIDGET_H

#include <QWidget>


/* Displays the QLabels and QSpinBoxes for the RGBA values
 */
class CColorRgbaWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CColorRgbaWidget(QWidget *parent = nullptr);

Q_SIGNALS:
    void ColorChanged(QColor);

public slots:
    void SetColor(QColor);

protected:
    virtual void paintEvent(QPaintEvent* pEvent) override;

private:
    void AddLayout();
    void AddConnections();

    void CheckRgbaValues();
    void UpdateControls();

private slots:
    void RgbaChanged();

private:
    class QSpinBox* m_pSpinBoxes[4];  // [0]: Red, [1]: Green, [2]: Blue, [3]: Alpha
    QColor m_color;
};

#endif // CCOLORRGBAWIDGET_H
