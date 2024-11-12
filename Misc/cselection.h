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

private:
    QRect  m_rect;
    QPoint m_startingPoint;
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

private:
    QRect m_rect;
    QPoint m_startingPoint;
};

#endif // CSELECTION_H
