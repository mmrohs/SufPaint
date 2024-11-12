#ifndef CELLIPSESELECTIONTOOL_H
#define CELLIPSESELECTIONTOOL_H

#include "ctool.h"


class CEllipseSelectionTool : public CTool
{
public:
    explicit CEllipseSelectionTool();

    virtual QString GetToolName() override;
    virtual QString GetTooltip() override;
    virtual QIcon   GetToolIcon() override;

    virtual void ProcessMousePressEvent(QMouseEvent* pEvent) override;
    virtual void ProcessMouseReleaseEvent(QMouseEvent* pEvent) override;
    virtual void ProcessMouseMoveEvent(QMouseEvent* pEvent) override;
};

#endif // CELLIPSESELECTIONTOOL_H
