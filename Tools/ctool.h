#ifndef CTOOL_H
#define CTOOL_H

#include <QIcon>
#include <QImage>
#include <QMouseEvent>
#include "../Enums.h"


// Abstract base class for all tools
class CTool
{
public:
    explicit CTool(EnumTools eTool);
    virtual ~CTool();

    EnumTools GetToolEnum() const;

    virtual QString GetToolName() = 0;
    virtual QString GetTooltip() = 0;
    virtual QIcon   GetToolIcon() = 0;

    virtual void ProcessMousePressEvent(QPoint pos, QMouseEvent* pEvent) = 0;

protected:
    QImage* GetImage() const;

private:
    EnumTools m_eTool;
};

#endif // CTOOL_H
