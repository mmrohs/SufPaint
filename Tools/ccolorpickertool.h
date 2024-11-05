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

    virtual void ProcessMousePressEvent(QMouseEvent* pEvent, CImageView* pView) override;
};

#endif // CCOLORPICKERTOOL_H
