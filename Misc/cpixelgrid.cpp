#include "cpixelgrid.h"
#include <QPainter>
#include "cscale.h"
#include "../Management/CImageManager.h"
#include "../Management/CImageViewManager.h"


CPixelGrid::CPixelGrid()
{
    InitPixmap();
}

void CPixelGrid::InitPixmap()
{
    m_tile = QPixmap(GetMaxScale(), GetMaxScale());
    m_tile.fill(Qt::transparent);

    QPainter pt(&m_tile);
    pt.setPen(GetDefaultPen());
    pt.drawLine(0, 0, GetMaxScale(), 0);
    pt.drawLine(0, 0, 0, GetMaxScale());
    pt.end();
}

void CPixelGrid::Draw(class QPainter& painter) const
{
    if (CheckRequirements())
    {
        qreal scale = GetScale();
        QPixmap pixmap = m_tile.copy(QRect(0, 0, scale, scale));
        painter.drawTiledPixmap(painter.clipBoundingRect(), pixmap);
    }
}

bool CPixelGrid::CheckRequirements() const
{
    // minimum scale to show the pixel grid
    static const qreal MINSCALE = 10.0;

    if (m_tile.isNull())
        return false;

    if (!CImageManager::GetImageManager()->HasImage())
        return false;

    return GetScale() >= MINSCALE;
}

qreal CPixelGrid::GetScale() const
{
    return CImageViewManager::GetImageViewManager()->GetScale();
}

qreal CPixelGrid::GetMaxScale() const
{
    return CScale::GetMaxScale();
}

QPen CPixelGrid::GetDefaultPen() const
{
    static QPen PEN = QPen(Qt::darkGray, Qt::DotLine);
    return PEN;
}
