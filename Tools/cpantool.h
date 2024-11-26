#ifndef CPANTOOL_H
#define CPANTOOL_H

#include "ctool.h"


/* Tool for moving the image view
*/
class CPanTool : public CTool
{
public:
    explicit CPanTool();

    virtual QIcon   GetToolIcon() const override;
    virtual QString GetToolName() const override;
    virtual QString GetTooltip() const override;

protected:
    // events for the left mouse button
    virtual void ProcessMouseLPressEvent(QMouseEvent* pEvent) override;
    virtual void ProcessMouseLMoveEvent(QMouseEvent* pEvent) override;

private:
    void MoveImageView();

private:
    QPoint m_startPos;
    QPoint m_endPos;
};

#endif // CPANTOOL_H
