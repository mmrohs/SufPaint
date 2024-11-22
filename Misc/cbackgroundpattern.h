#ifndef CPIXELGRID_H
#define CPIXELGRID_H

#include <QObject>
#include <QPixmap>


/* class for drawing the pixel grid
*/
class CPixelGrid
{
public:
    CPixelGrid();

    void DrawPixelGrid(class QPainter&);

private:
    // returns true if all requirements for the pixelgrid are met
    bool CheckRequirements() const;

    qreal GetScale() const;
    qreal GetMaxScale() const;
    QPen GetDefaultPen() const;

private:
    QPixmap m_tile;
};

#endif // CPIXELGRID_H
