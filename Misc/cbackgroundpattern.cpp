#include "cbackgroundpattern.h"
#include <QPainter>

// size constants for the pattern
#define TILESIZE 8
#define PATTERNSIZE 2 * TILESIZE


CBackgroundPattern::CBackgroundPattern()
{
    InitPixmap();
}

void CBackgroundPattern::InitPixmap()
{
    m_tile = QPixmap(PATTERNSIZE, PATTERNSIZE);
    m_tile.fill(Qt::white);

    QPainter pt(&m_tile);
    pt.fillRect(0, 0, TILESIZE, TILESIZE, Qt::gray);
    pt.fillRect(TILESIZE, TILESIZE, PATTERNSIZE, PATTERNSIZE, Qt::gray);
    pt.end();
}

void CBackgroundPattern::Draw(class QPainter& painter) const
{
    if (m_tile.isNull())
        return;

    painter.drawTiledPixmap(painter.clipBoundingRect(), m_tile);
}
