#ifndef CCOLORHISTORYWIDGET_H
#define CCOLORHISTORYWIDGET_H

#include <QWidget>

class CColorHistoryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CColorHistoryWidget(QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent* pEvent) override;
};

#endif // CCOLORHISTORYWIDGET_H
