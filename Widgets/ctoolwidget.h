#ifndef CTOOLWIDGET_H
#define CTOOLWIDGET_H

#include <QGroupBox>
#include "../Enums.h"


class CToolWidget : public QGroupBox
{
public:
    explicit CToolWidget(QWidget* pParent);

public slots:
    void ImagePropertiesChanged();
    void ToolChanged();

private:
    void AddLayout();
    void AddToolButtons();
    void EnableTools();

private:
    class QGridLayout* m_pGridLayout;
    std::vector<class CToolButton*> m_vecTools;
    bool m_bEnabled;
};

#endif // CTOOLWIDGET_H
