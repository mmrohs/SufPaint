#ifndef CTOOL_H
#define CTOOL_H

#include <QIcon>
#include <QImage>
#include <QMouseEvent>
#include "../Enums.h"

class CImageView;

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

    virtual void ProcessMousePressEvent(QMouseEvent* pEvent, CImageView* pView) = 0;
    virtual void ProcessMouseReleaseEvent(QMouseEvent* pEvent, CImageView* pView);
    virtual void ProcessMouseMoveEvent(QMouseEvent* pEvent, CImageView* pView);

protected:
    QImage* GetImage() const;

private:
    EnumTools m_eTool;
};

#endif // CTOOL_H
