#ifndef CRECTANGLESELECTIONTOOL_H
#define CRECTANGLESELECTIONTOOL_H

#include "ctool.h"


class CRectangleSelectionTool : public CTool
{
public:
    explicit CRectangleSelectionTool();

    virtual void ProcessMousePressEvent(QPoint pos, QMouseEvent* pEvent) override;
};

#endif // CRECTANGLESELECTIONTOOL_H
