#include "cselection.h"
#include <QPainter>
#include "../Management/CImageViewManager.h"


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

QPoint CSelection::GetImagePos(QPoint widgetPos) const
{
    return CImageViewManager::GetImageViewManager()->GetImagePos(widgetPos, true);
}

QPoint CSelection::GetWidgetPos(QPoint imagePos) const
{
    return CImageViewManager::GetImageViewManager()->GetWidgetPos(imagePos);
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
    QRect rect(GetWidgetPos(m_rect.topLeft()), GetWidgetPos(m_rect.bottomRight()));
    paint.setPen(GetDefaultPen());
    paint.drawRect(rect);
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
    QRect rect(GetWidgetPos(m_rect.topLeft()), GetWidgetPos(m_rect.bottomRight()));
    paint.setPen(GetDefaultPen());
    paint.drawEllipse(rect);
}
