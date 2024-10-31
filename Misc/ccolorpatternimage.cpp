#include "ccolorpatternimage.h"

#define G_OFFSET 6    // width of the gray scale next to the color palette


CColorPatternImage::CColorPatternImage(QSize size)
    : QImage(size, QImage::Format_ARGB32)
{
    GeneratePatternImage();
}

CColorPatternImage::CColorPatternImage(int width, int height)
    : QImage(width, height, QImage::Format_ARGB32)
{
    GeneratePatternImage();
}

QColor CColorPatternImage::GetColorFromPos(int x, int y) const
{
    return GetColorFromPos(QPointF(x, y));
}

QColor CColorPatternImage::GetColorFromPos(QPointF pos) const
{
    int r = CalcRed(pos);
    int g = CalcGreen(pos);
    int b = CalcBlue(pos);
    return QColor(r, g, b, 255);
}

void CColorPatternImage::GeneratePatternImage()
{
    for (int y = 0; y < height(); ++y)
    {
        QRgb* pLine = reinterpret_cast<QRgb*>(scanLine(y));
        for (int x = 0; pLine != NULL && x < width(); ++x)
        {
            pLine[x] = GetColorFromPos(QPointF(x,y)).rgba();
        }
    }
}

int CColorPatternImage::CalcRed(QPointF pos) const
{
    return CalcColor(pos, 0);
}

int CColorPatternImage::CalcGreen(QPointF pos) const
{
    return CalcColor(pos, 2.0/3.0);
}

int CColorPatternImage::CalcBlue(QPointF pos) const
{
    return CalcColor(pos, 1.0/3.0);
}

/* Calculates the color value
 *
 * The horizontal gradient can be modeled with a triangle function
 * shifted by an RGB-dependant offset. The vertical gradient is complicated.
 */
int CColorPatternImage::CalcColor(QPointF pos, double rgbOffset) const
{
    double c = 255.0;
    double x = pos.x();
    double y = pos.y();
    double h = height();
    double w = width();
    double wo = w - G_OFFSET;
    double xs = x + wo * rgbOffset;
    if (x < wo && xs > wo)
        xs -= wo;
    double dx = xs / (0.5 * wo);
    double dy = y / h;    // 0.0...1.0

    // horizontal gradient
    if (xs <= 0.5 * wo)
    {
        c *= 2.0 - 3.0 * dx;
    }
    else if (xs > 0.5 * wo && xs <= wo)
    {
        c *= -4.0 + 3.0 * dx;
    }
    else
    {
        c *= 0.5;
    }

    // prevent values below 0 and above 255
    c = __max(0, __min(c, 255.0));

    // vertical gradient
    if (dy <= 0.5)
    {
        double ys = h - y;
        c *= 2.0 * (1.0 - (ys / h));
        c += 255 * (1.0 - 2.0 * y / h);
    }
    else if (dy > 0.5)
    {
        c *= 2.0 * (1.0 - dy);
    }

    return __max(0, __min(c, 255.0));
}
