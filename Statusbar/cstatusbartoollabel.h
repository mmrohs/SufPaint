#ifndef CSTATUSBARTOOLLABEL_H
#define CSTATUSBARTOOLLABEL_H

#include <QLabel>


class CStatusBarToolLabel : public QLabel
{
public:
    explicit CStatusBarToolLabel(QWidget* pParent);

    void Update();
};

#endif // CSTATUSBARTOOLLABEL_H
