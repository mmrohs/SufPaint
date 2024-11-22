#ifndef CRECTANGLESELECTIONTOOL_H
#define CRECTANGLESELECTIONTOOL_H

#include "ctool.h"


/* Tool for selecting rectangular areas inside the image
*/
class CRectangleSelectionTool : public CTool
{
public:
    explicit CRectangleSelectionTool();

    virtual QIcon   GetToolIcon() const override;
    virtual QString GetToolName() const override;
    virtual QString GetTooltip() const override;
    virtual QString GetStatusText() const override;

protected:
    // events for the left mouse button
    virtual void ProcessMouseLPressEvent(QMouseEvent* pEvent) override;
    virtual void ProcessMouseLReleaseEvent(QMouseEvent* pEvent) override;
    virtual void ProcessMouseLMoveEvent(QMouseEvent* pEvent) override;

    // events for the right mouse button
    virtual void ProcessMouseRPressEvent(QMouseEvent* pEvent) override;
};

#endif // CRECTANGLESELECTIONTOOL_H
