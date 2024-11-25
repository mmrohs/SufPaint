#ifndef CGRADIENTTOOL_H
#define CGRADIENTTOOL_H

#include "ctool.h"


class CGradientTool : public CTool
{
public:
    CGradientTool();

    virtual QIcon   GetToolIcon() const override;
    virtual QString GetToolName() const override;
    virtual QString GetTooltip() const override;

    virtual void ProcessMouseLPressEvent(QMouseEvent* pEvent) override;
    virtual void ProcessMouseLReleaseEvent(QMouseEvent* pEvent) override;
    virtual void ProcessMouseLMoveEvent(QMouseEvent* pEvent) override;

private:
    void ApplyGradient();
    QRgb CalculateColor(QPointF pos);
    void InitColors();
    void InitVectors();

private:
    // Positions / vectors
    QPointF m_startPos;
    QPointF m_endPos;
    QPointF m_diffPos;

    // (inverse) distance between m_startPos and m_endPos
    qreal m_diffLength;
    qreal m_invDiffLength;

    // colors
    QColor m_startColor;
    QColor m_endColor;
    QColor m_diffColor;
};

#endif // CGRADIENTTOOL_H
