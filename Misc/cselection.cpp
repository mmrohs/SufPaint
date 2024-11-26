#include "cselection.h"
#include <QPainter>
#include <QPainterPath>
#include "../Management/CImageViewManager.h"

#define INVALIDPOINT QPoint(-1,-1)


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

QPen CSelection::GetDefaultPen(bool bScale) const
{
    static const QPen PEN = QPen(QBrush(QColor(50,50,255,255)), 1, Qt::DotLine);
    if (bScale)
    {
        QPen pen(PEN);
        qreal scale = CImageViewManager::GetImageViewManager()->GetScale();
        pen.setWidthF(pen.widthF() / scale);
        return pen;
    }
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
    : CSelection(SelectionType::RECTANGLE), m_startPoint(INVALIDPOINT)
{
}

/*virtual*/ void CRectangleSelection::AddCoordinate(QPoint pos)
{
    if (m_startPoint == INVALIDPOINT)
    {
        m_startPoint = pos;
    }
    m_endPoint = pos;
}

/*virtual*/ bool CRectangleSelection::Contains(QPoint pos) const
{
    return GetBoundingRect().contains(pos);
}

/*virtual*/ QRect CRectangleSelection::GetBoundingRect() const
{
    return QRect(m_startPoint, m_endPoint);
}

/*virtual*/ void CRectangleSelection::Paint(class QPainter& paint) const
{
    QRect imageRect = GetBoundingRect();
    QPoint posTopLeft = GetWidgetPos(imageRect.topLeft());
    QPoint posBottomRight = GetWidgetPos(imageRect.bottomRight());
    QRect widgetRect(posTopLeft, posBottomRight);
    paint.fillRect(widgetRect, GetDefaultBrush());
    paint.setPen(GetDefaultPen(true));
    paint.drawRect(widgetRect);
}



// ########## CEllipticSelection ##########

CEllipticSelection::CEllipticSelection()
    : CSelection(SelectionType::ELLIPSE),  m_startPoint(INVALIDPOINT), m_endPoint(INVALIDPOINT)
{
}

/*virtual*/ void CEllipticSelection::AddCoordinate(QPoint pos)
{
    if (m_startPoint == INVALIDPOINT)
    {
        m_startPoint = pos;
    }
    m_endPoint = pos;
}

/*virtual*/ bool CEllipticSelection::Contains(QPoint pos) const
{
    // check bounding box (fast)
    QRect rect = GetBoundingRect();
    if (!rect.contains(pos))
        return false;

    QPointF diff = m_endPoint - m_startPoint;
    qreal a = 0.5 * diff.x();
    qreal b = 0.5 * diff.y();

    QPointF center = m_startPoint + 0.5 * diff;

    // check equation x²/a² + y²/b² <= 1
    QPointF distFromCenter = pos - center;
    qreal x = distFromCenter.x();
    qreal y = distFromCenter.y();
    return (x * x / (a * a)) + (y * y / (b * b)) <= 1.0;
}

/*virtual*/ QRect CEllipticSelection::GetBoundingRect() const
{
    return QRect(m_startPoint, m_endPoint);
}

/*virtual*/ void CEllipticSelection::Paint(class QPainter& paint) const
{
    QRect imageRect = GetBoundingRect();
    QPoint posTopLeft = GetWidgetPos(imageRect.topLeft());
    QPoint posBottomRight = GetWidgetPos(imageRect.bottomRight());
    QRect widgetRect(posTopLeft, posBottomRight);
    QPainterPath path;
    path.addEllipse(widgetRect);
    paint.fillPath(path, GetDefaultBrush());
    paint.setPen(GetDefaultPen(true));
    paint.drawEllipse(widgetRect);
}
