#ifndef CBRUSHTOOL_H
#define CBRUSHTOOL_H

#include "ctool.h"


class CBrushTool : public CTool
{
public:
    explicit CBrushTool();

    virtual QString GetToolName() override;
    virtual QString GetTooltip() override;
    virtual QIcon   GetToolIcon() override;

    virtual void ProcessMouseLPressEvent(QMouseEvent* pEvent) override;
};

#endif // CBRUSHTOOL_H
