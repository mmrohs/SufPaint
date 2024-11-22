#ifndef CTOOL_H
#define CTOOL_H

#include <QIcon>
#include <QImage>
#include <QMouseEvent>
#include "../Enums.h"

//class CImageView;

/* Abstract base class for all tools
*/
class CTool
{
public:
    explicit CTool(EnumTools eTool);
    virtual ~CTool();

    EnumTools GetToolEnum() const;

    // events for any mouse button
    void ProcessMousePressEvent(QMouseEvent* pEvent);
    void ProcessMouseReleaseEvent(QMouseEvent* pEvent);
    void ProcessMouseMoveEvent(QMouseEvent* pEvent);

    // tool properties
    // (reimplement these in derived classes!)
    virtual QIcon   GetToolIcon() const = 0;
    virtual QString GetToolName() const = 0;
    virtual QString GetTooltip() const = 0;
    virtual QString GetStatusText() const { return GetToolName(); };

protected:
    // events for left mouse button
    // (reimplement these in derived classes if necessary)
    virtual void ProcessMouseLPressEvent(QMouseEvent* pEvent) {};
    virtual void ProcessMouseLReleaseEvent(QMouseEvent* pEvent) {};
    virtual void ProcessMouseLMoveEvent(QMouseEvent* pEvent) {};

    // events for right mouse button
    // (reimplement these in derived classes if necessary)
    virtual void ProcessMouseRPressEvent(QMouseEvent* pEvent) {};
    virtual void ProcessMouseRReleaseEvent(QMouseEvent* pEvent) {};

    // returns the image pointer or NULL if no image loaded
    QImage* GetImage() const;

    // returns the mouse position in the image coordinate system
    QPoint GetImagePos(QPoint widgetPos) const;
    QPoint GetImagePos(QMouseEvent* pEvent, bool bCheck) const;

    // check if the given position is inside the image rect in the widget system
    // if not then it gets moved to the nearest image rect coordinate
    QPoint CheckPositionInImageRect(QPoint widgetPos) const;

    // returns the mouse coordinate in the image coordinate system
    // returns QPoint(-1,-1) if any error occurs or if the mouse is not inside the image rect
    QPoint GetMouseCoordinateFromEvent(QMouseEvent* pEvent) const;

private:
    EnumTools m_eTool;
};

#endif // CTOOL_H
