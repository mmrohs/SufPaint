#ifndef CSELECTION_H
#define CSELECTION_H

#include <QRect>
#include <QPen>


/* abstract base class for user defined selections inside the image
*/
class CSelection
{
protected:
    enum SelectionType { NONE, RECTANGLE, ELLIPSE, CUSTOM };

public:
    CSelection(SelectionType);
    virtual ~CSelection();

    bool IsValid() const;

    virtual void AddCoordinate(QPoint) = 0;
    virtual QRect GetBoundingRect() const = 0;
    virtual void Paint(class QPainter&) const = 0;

protected:
    QPen GetDefaultPen() const;
    QBrush GetDefaultBrush() const;

    // coordinate transformations
    QPoint GetImagePos(QPoint widgetPos) const;
    QPoint GetWidgetPos(QPoint imagePos) const;

protected:
    SelectionType m_type;
};


/* Derived class: Rectangle Selection
*/
class CRectangleSelection : public CSelection
{
public:
    explicit CRectangleSelection();

    virtual void AddCoordinate(QPoint) override;
    virtual QRect GetBoundingRect() const override;
    virtual void Paint(class QPainter&) const override;

protected:
    QPen GetPen() const;

private:
    QRect  m_rect;
    QPoint m_startingPoint;
    bool   m_bSetStartingPoint;
};


/* Derived class: Elliptic Selection
*/
class CEllipticSelection : public CSelection
{
public:
    explicit CEllipticSelection();

    virtual void AddCoordinate(QPoint) override;
    virtual QRect GetBoundingRect() const override;
    virtual void Paint(class QPainter&) const override;

protected:
    QPen GetPen() const;

private:
    QRect m_rect;
    QPoint m_startingPoint;
    bool   m_bSetStartingPoint;
};

#endif // CSELECTION_H
