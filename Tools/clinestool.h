#ifndef CLINESTOOL_H
#define CLINESTOOL_H

#include "ctool.h"


class CLinesTool : public CTool
{
public:
    explicit CLinesTool();

    virtual QIcon   GetToolIcon() const override;
    virtual QString GetToolName() const override;
    virtual QString GetTooltip() const override;

    virtual void ProcessMouseLPressEvent(QMouseEvent* pEvent) override;
};

#endif // CLINESTOOL_H
