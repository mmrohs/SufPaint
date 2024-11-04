#ifndef CBUCKETTOOL_H
#define CBUCKETTOOL_H

#include "ctool.h"


class CBucketTool : public CTool
{
public:
    CBucketTool();

    virtual QString GetToolName() override;
    virtual QString GetTooltip() override;
    virtual QIcon   GetToolIcon() override;

    virtual void ProcessMousePressEvent(QPoint pos, QMouseEvent* pEvent) override;
};

#endif // CBUCKETTOOL_H
