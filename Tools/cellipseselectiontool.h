#ifndef CELLIPSESELECTIONTOOL_H
#define CELLIPSESELECTIONTOOL_H

#include "ctool.h"


/* Tool for selecting elliptic areas inside the image
*/
class CEllipseSelectionTool : public CTool
{
public:
    explicit CEllipseSelectionTool();

    virtual QString GetToolName() override;
    virtual QString GetTooltip() override;
    virtual QIcon   GetToolIcon() override;

protected:
    // events for the left mouse button
    virtual void ProcessMouseLPressEvent(QMouseEvent* pEvent) override;
    virtual void ProcessMouseLReleaseEvent(QMouseEvent* pEvent) override;
    virtual void ProcessMouseLMoveEvent(QMouseEvent* pEvent) override;

    // events for the right mouse button
    virtual void ProcessMouseRPressEvent(QMouseEvent* pEvent) override;
};

#endif // CELLIPSESELECTIONTOOL_H
