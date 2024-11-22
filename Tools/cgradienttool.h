#ifndef CGRADIENTTOOL_H
#define CGRADIENTTOOL_H

#include "ctool.h"


class CGradientTool : public CTool
{
public:
    CGradientTool();

    virtual QIcon   GetToolIcon() const override;
    virtual QString GetToolName() const override;
    virtual QString GetTooltip() const override;

    virtual void ProcessMouseLPressEvent(QMouseEvent* pEvent) override;
};

#endif // CGRADIENTTOOL_H
