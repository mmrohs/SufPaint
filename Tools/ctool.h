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

    virtual void ProcessMousePressEvent(QMouseEvent* pEvent) = 0;
    virtual void ProcessMouseReleaseEvent(QMouseEvent* pEvent);
    virtual void ProcessMouseMoveEvent(QMouseEvent* pEvent);

protected:
    QImage* GetImage() const;

    // determines the mouse position in the image coordinate system
    // the second parameter controls whether positions outside the image get corrected into the image
    QPoint GetImagePos(QMouseEvent* pEvent, bool bCheckPosition);

private:
    EnumTools m_eTool;
};

#endif // CTOOL_H
