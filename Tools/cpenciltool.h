#ifndef CPENCILTOOL_H
#define CPENCILTOOL_H

#include "ctool.h"


class CPencilTool : public CTool
{
public:
    explicit CPencilTool();

    virtual QIcon   GetToolIcon() const override;
    virtual QString GetToolName() const override;
    virtual QString GetTooltip() const override;

    virtual void ProcessMouseLPressEvent(QMouseEvent* pEvent) override;
};

#endif // CPENCILTOOL_H
