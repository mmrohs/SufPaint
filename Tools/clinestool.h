#ifndef CLINESTOOL_H
#define CLINESTOOL_H

#include "ctool.h"


class CLinesTool : public CTool
{
public:
    explicit CLinesTool();

    virtual QString GetToolName() override;
    virtual QString GetTooltip() override;
    virtual QIcon   GetToolIcon() override;

    virtual void ProcessMouseLPressEvent(QMouseEvent* pEvent) override;
};

#endif // CLINESTOOL_H
