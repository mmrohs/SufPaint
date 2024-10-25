#ifndef CSTATUSBARZOOMLABEL_H
#define CSTATUSBARZOOMLABEL_H

#include <QLabel>

class CStatusBarZoomLabel : public QLabel
{
public:
    explicit CStatusBarZoomLabel(QWidget* pParent);

    void Update();

private:
    void SetZoom(qreal zoom);
};

#endif // CSTATUSBARZOOMLABEL_H
