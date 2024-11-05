#ifndef CGRADIENTTOOL_H
#define CGRADIENTTOOL_H

#include "ctool.h"


class CGradientTool : public CTool
{
public:
    CGradientTool();

    virtual QString GetToolName() override;
    virtual QString GetTooltip() override;
    virtual QIcon   GetToolIcon() override;

    virtual void ProcessMousePressEvent(QMouseEvent* pEvent, CImageView* pView) override;
};

#endif // CGRADIENTTOOL_H
