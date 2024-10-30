#ifndef CCOLORWIDGET_H
#define CCOLORWIDGET_H

#include <QGroupBox>

class CColorWidget : public QGroupBox
{
    Q_OBJECT
public:
    explicit CColorWidget(QWidget* pParent);

Q_SIGNALS:
    void UpdateForegroundColor(QColor);
    void UpdateBackgroundColor(QColor);

public slots:
    void ColorPickedRgb(QColor color);
    void ColorPickedRgba(QColor color);
    void ColorsSwitched();

protected:
    virtual void paintEvent(QPaintEvent* pEvent) override;

private:
    void AddLayout();
    void AddConnections();

    void CheckRgbaValues();
    void DrawColorRect(QRect rect, QColor color);

private:
    class CColorPreviewWidget* m_pColPrevWidget;
    class CColorHistoryWidget* m_pColHistWidget;
    class CColorRgbaWidget*    m_pColRgbaWidget;
    class CColorPaletteWidget* m_pColPalWidget;
    class QCheckBox*           m_pChkLight;

    QColor m_foregroundColor;
    QColor m_backgroundColor;
};

#endif // CCOLORWIDGET_H
