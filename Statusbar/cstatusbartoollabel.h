#ifndef CSTATUSBARTOOLLABEL_H
#define CSTATUSBARTOOLLABEL_H

#include <QLabel>
#include "../Enums.h"


class CStatusBarToolLabel : public QLabel
{
public:
    explicit CStatusBarToolLabel(QWidget* pParent);

    void Update();

private:
    void SetTool(EnumTools tool);
    void UpdateText();

private:
    EnumTools m_tool;
};

#endif // CSTATUSBARTOOLLABEL_H
