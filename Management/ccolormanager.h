#ifndef CCOLORMANAGER_H
#define CCOLORMANAGER_H

#include <QObject>
#include <QColor>


class CColorManager : public QObject
{
    Q_OBJECT
protected:
    explicit CColorManager();

public:
    static CColorManager* GetColorManager();

    QColor GetForegroundColor() const;
    QColor GetBackgroundColor() const;
    void SetForegroundColor(QColor color, bool bIgnoreAlpha = false);
    void SetBackgroundColor(QColor color, bool bIgnoreAlpha = false);
    void SwitchColors();

Q_SIGNALS:
    void ColorUpdate();

private:
    static CColorManager* m_pSingletonInstance;
    QColor m_foregroundColor;
    QColor m_backgroundColor;
};

#endif // CCOLORMANAGER_H
