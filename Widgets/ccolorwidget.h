#ifndef CCOLORWIDGET_H
#define CCOLORWIDGET_H

#include <QGroupBox>

class CColorWidget : public QGroupBox
{
    Q_OBJECT
public:
    explicit CColorWidget(QWidget* pParent);

Q_SIGNALS:
    void ColorUpdate();

public slots:
    void ColorChanged();

protected:
    virtual void paintEvent(QPaintEvent* pEvent) override;

private:
    void AddLayout();
    void AddConnections();

    void CheckRgbaValues();

private:
    // child widgets
    class CColorPreviewWidget* m_pColPrevWidget;
    class CColorHistoryWidget* m_pColHistWidget;
    class CColorRgbaWidget*    m_pColRgbaWidget;
    class CColorPaletteWidget* m_pColPalWidget;
};

#endif // CCOLORWIDGET_H
