#ifndef CRECTANGLESELECTIONTOOL_H
#define CRECTANGLESELECTIONTOOL_H

#include "ctool.h"


class CRectangleSelectionTool : public CTool
{
public:
    explicit CRectangleSelectionTool();

    virtual QString GetToolName() override;
    virtual QString GetTooltip() override;
    virtual QIcon   GetToolIcon() override;

    virtual void ProcessMousePressEvent(QMouseEvent* pEvent, CImageView* pView) override;
    virtual void ProcessMouseReleaseEvent(QMouseEvent* pEvent, CImageView* pView) override;
    virtual void ProcessMouseMoveEvent(QMouseEvent* pEvent, CImageView* pView) override;

private:
    QRect m_selectionRect;
};

#endif // CRECTANGLESELECTIONTOOL_H
