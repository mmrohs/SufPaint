#ifndef CPENCILTOOL_H
#define CPENCILTOOL_H

#include "ctool.h"


class CPencilTool : public CTool
{
public:
    explicit CPencilTool();

    virtual QString GetToolName() override;
    virtual QString GetTooltip() override;
    virtual QIcon   GetToolIcon() override;

    virtual void ProcessMousePressEvent(QPoint pos, QMouseEvent* pEvent) override;
};

#endif // CPENCILTOOL_H
