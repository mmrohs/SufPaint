#include "cpixelgrid.h"
#include <QPainter>
#include "cscale.h"
#include "../Management/CImageManager.h"
#include "../Management/CImageViewManager.h"


CPixelGrid::CPixelGrid()
    : m_tile(QPixmap(GetMaxScale(), GetMaxScale()))
{
    m_tile.fill(Qt::transparent);
    QPainter pt(&m_tile);
    pt.setPen(GetDefaultPen());
    pt.drawLine(0, 0, GetMaxScale(), 0);
    pt.drawLine(0, 0, 0, GetMaxScale());
    pt.end();
}

void CPixelGrid::DrawPixelGrid(class QPainter& painter)
{
    if (CheckRequirements())
    {
        qreal scale = GetScale();
        painter.scale(1.0/scale, 1.0/scale);

        QPixmap pixmap = m_tile.copy(QRect(0, 0, scale, scale));
        painter.drawTiledPixmap(painter.clipBoundingRect(), pixmap);

        painter.scale(scale, scale);
    }
}

bool CPixelGrid::CheckRequirements() const
{
    // minimum scale to show the pixel grid
    static const qreal MINSCALE = 20.0;

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