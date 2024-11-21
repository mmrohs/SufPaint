#include "cselection.h"
#include <QPainter>
#include <QPainterPath>
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
    static const QPen PEN = QPen(QBrush(QColor(50,50,255,255)), 1, Qt::DashLine);
    return PEN;
}

QBrush CSelection::GetDefaultBrush() const
{
    static const QBrush BRUSH = QBrush(QColor(200,200,255,80));
    return BRUSH;
}

QPoint CSelection::GetImagePos(QPoint widgetPos) const
{
    CImageViewManager* pViewManager = CImageViewManager::GetImageViewManager();
    QPoint imagePos = pViewManager->GetImagePos(widgetPos);
    imagePos = pViewManager->CheckPositionInImage(imagePos);
    return imagePos;
}

QPoint CSelection::GetWidgetPos(QPoint imagePos) const
{
    return CImageViewManager::GetImageViewManager()->GetWidgetPos(imagePos);
}



// ########## CRectangleSelection ##########

CRectangleSelection::CRectangleSelection()
    : CSelection(SelectionType::RECTANGLE), m_bSetStartingPoint(true)
{
}

/*virtual*/ void CRectangleSelection::AddCoordinate(QPoint pos)
{
    if (m_bSetStartingPoint)
    {
        m_startingPoint = pos;
        m_bSetStartingPoint = false;
    }
    m_rect = QRect(m_startingPoint, pos);
}

/*virtual*/ QRect CRectangleSelection::GetBoundingRect() const
{
    return m_rect;
}

QPen CRectangleSelection::GetPen() const
{
    qreal scale = CImageViewManager::GetImageViewManager()->GetScale();
    QPen pen = GetDefaultPen();
    pen.setWidthF(pen.widthF() / scale);
    return pen;
}

/*virtual*/ void CRectangleSelection::Paint(class QPainter& paint) const
{
    QPoint posTopLeft = GetWidgetPos(m_rect.topLeft());
    QPoint posBottomRight = GetWidgetPos(m_rect.bottomRight());
    QRect rect(posTopLeft, posBottomRight);
    paint.fillRect(rect, GetDefaultBrush());
    paint.setPen(GetPen());
    paint.drawRect(rect);
}



// ########## CEllipticSelection ##########

CEllipticSelection::CEllipticSelection()
    : CSelection(SelectionType::ELLIPSE), m_bSetStartingPoint(true)
{
}

/*virtual*/ void CEllipticSelection::AddCoordinate(QPoint pos)
{
    if (m_bSetStartingPoint)
    {
        m_startingPoint = pos;
        m_bSetStartingPoint = false;
    }
    m_rect = QRect(m_startingPoint, pos);
}

/*virtual*/ QRect CEllipticSelection::GetBoundingRect() const
{
    return m_rect;
}

QPen CEllipticSelection::GetPen() const
{
    qreal scale = CImageViewManager::GetImageViewManager()->GetScale();
    QPen pen = GetDefaultPen();
    pen.setWidthF(pen.widthF() / scale);
    return pen;
}

/*virtual*/ void CEllipticSelection::Paint(class QPainter& paint) const
{
    QPoint posTopLeft = GetWidgetPos(m_rect.topLeft());
    QPoint posBottomRight = GetWidgetPos(m_rect.bottomRight());
    QRect rect(posTopLeft, posBottomRight);
    QPainterPath path;
    path.addEllipse(rect);
    paint.fillPath(path, GetDefaultBrush());
    paint.setPen(GetPen());
    paint.drawEllipse(rect);
}
