#ifndef CCOLORPICKERTOOL_H
#define CCOLORPICKERTOOL_H

#include "ctool.h"


class CColorPickerTool : public CTool
{
public:
    explicit CColorPickerTool();

    virtual QString GetToolName() override;
    virtual QString GetTooltip() override;
    virtual QIcon   GetToolIcon() override;

    virtual void ProcessMousePressEvent(QPoint pos, QMouseEvent* pEvent) override;
};

#endif // CCOLORPICKERTOOL_H
