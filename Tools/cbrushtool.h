#ifndef CBRUSHTOOL_H
#define CBRUSHTOOL_H

#include "ctool.h"


class CBrushTool : public CTool
{
public:
    explicit CBrushTool();

    virtual QIcon   GetToolIcon() const override;
    virtual QString GetToolName() const override;
    virtual QString GetTooltip() const override;

    virtual void ProcessMouseLPressEvent(QMouseEvent* pEvent) override;
};

#endif // CBRUSHTOOL_H
