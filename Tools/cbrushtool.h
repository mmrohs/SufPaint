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

    virtual void ProcessMousePressEvent(QMouseEvent* pEvent, CImageView* pView) override;
};

#endif // CBRUSHTOOL_H
