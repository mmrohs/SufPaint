#ifndef CBUCKETTOOL_H
#define CBUCKETTOOL_H

#include "ctool.h"


class CBucketTool : public CTool
{
public:
    CBucketTool();

    virtual QIcon   GetToolIcon() const override;
    virtual QString GetToolName() const override;
    virtual QString GetTooltip() const override;

    virtual void ProcessMouseLPressEvent(QMouseEvent* pEvent) override;
};

#endif // CBUCKETTOOL_H
