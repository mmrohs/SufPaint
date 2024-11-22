#ifndef CCOLORPICKERTOOL_H
#define CCOLORPICKERTOOL_H

#include "ctool.h"


class CColorPickerTool : public CTool
{
public:
    explicit CColorPickerTool();

    virtual QIcon   GetToolIcon() const override;
    virtual QString GetToolName() const override;
    virtual QString GetTooltip() const override;

    virtual void ProcessMouseLPressEvent(QMouseEvent* pEvent) override;
};

#endif // CCOLORPICKERTOOL_H
