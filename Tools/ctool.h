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

    QString   GetToolName() const;
    EnumTools GetToolEnum() const;

    static QString GetToolName(EnumTools);
    static QString GetTooltip(EnumTools);
    static QIcon   GetToolIcon(EnumTools);

    virtual void ProcessMousePressEvent(QPoint pos, QMouseEvent* pEvent) = 0;

protected:
    QImage* GetImage() const;

private:
    EnumTools m_eTool;
};

#endif // CTOOL_H
