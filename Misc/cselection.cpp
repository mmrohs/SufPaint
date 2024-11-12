#include "cselection.h"
#include <QPainter>


// ########## CSelection ##########

CSelection::CSelection(SelectionType type)
    : m_type(type)
{
}

/*virtual*/ CSelection::~CSelection()
{
}

bool CSelection::IsValid() const
{
    return m_type != SelectionType::NONE;
}

QPen CSelection::GetDefaultPen() const
{
    static const QPen PEN = QPen(QBrush(Qt::red), 2, Qt::DashLine);
    return PEN;
}



// ########## CRectangleSelection ##########

CRectangleSelection::CRectangleSelection()
    : CSelection(SelectionType::RECTANGLE)
{
}

/*virtual*/ void CRectangleSelection::AddCoordinate(QPoint pos)
{
    if (m_startingPoint.isNull())
    {
        m_startingPoint = pos;
    }
    m_rect = QRect(m_startingPoint, pos);
}

/*virtual*/ QRect CRectangleSelection::GetBoundingRect() const
{
    return m_rect;
}

/*virtual*/ void CRectangleSelection::Paint(class QPainter& paint) const
{
    paint.setPen(GetDefaultPen());
    paint.drawRect(m_rect);
}



// ########## CEllipticSelection ##########

CEllipticSelection::CEllipticSelection()
    : CSelection(SelectionType::ELLIPSE)
{
}

/*virtual*/ void CEllipticSelection::AddCoordinate(QPoint pos)
{
    if (m_startingPoint.isNull())
    {
        m_startingPoint = pos;
    }
    m_rect = QRect(m_startingPoint, pos);
}

/*virtual*/ QRect CEllipticSelection::GetBoundingRect() const
{
    return m_rect;
}

/*virtual*/ void CEllipticSelection::Paint(class QPainter& paint) const
{
    paint.setPen(GetDefaultPen());
    paint.drawEllipse(m_rect);
}
