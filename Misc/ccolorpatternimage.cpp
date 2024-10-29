#include "ccolorpatternimage.h"

#define OFFSET 8    // offset for the color pattern and height of the gray scale at the top


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

QColor CColorPatternImage::GetColorFromPos(QPointF pos)
{
    int r = CalcRed(pos.x(), pos.y());
    int g = CalcGreen(pos.x(), pos.y());
    int b = CalcBlue(pos.x(), pos.y());
    return QColor(r, g, b, 255);
}

void CColorPatternImage::GeneratePatternImage()
{
    for (int y = 0; y < height(); ++y)
    {
        QRgb* pLine = reinterpret_cast<QRgb*>(scanLine(y));
        if (pLine == NULL)
            continue;

        for (int x = 0; x < width(); ++x)
        {
            int r = CalcRed(x,y);
            int g = CalcGreen(x,y);
            int b = CalcBlue(x,y);
            pLine[x] = qRgba(r, g, b, 255);
        }
    }
}

int CColorPatternImage::CalcRed(double x, double y) const
{
    double dx = (double) x / width();   // 0.0...1.0
    double step = (height() - OFFSET) / 6.0;

    if (y < OFFSET)
    {
        return dx * 255;
    }

    y -= OFFSET;
    if (y <= step || y >= 5 * step)
    {
        return dx * 255;
    }
    else if (y > step && y < 2 * step)
    {
        return dx * 255 * (2 * step - y) / step;
    }
    else if (y > 4 * step && y < 5 * step)
    {
        return dx * 255 * (y - 4 * step) / step;
    }
    else
    {
        return 0;
    }
}

int CColorPatternImage::CalcGreen(double x, double y) const
{
    double dx = (double) x / width();   // 0.0...1.0
    double step = (height() - OFFSET) / 6.0;

    if (y < OFFSET)
    {
        return dx * 255;
    }

    y -= OFFSET;
    if (y < step)
    {
        return dx * 255 * y / step;
    }
    else if (y >= step && y <= 3 * step)
    {
        return dx * 255;
    }
    else if (y > 3 * step && y < 4 * step)
    {
        return dx * 255 * (4 * step - y) / step;
    }
    else
    {
        return 0;
    }
}

int CColorPatternImage::CalcBlue(double x, double y) const
{
    double dx = (double) x / width();   // 0.0...1.0
    double step = (height() - OFFSET) / 6.0;

    if (y < OFFSET)
    {
        return dx * 255;
    }

    y -= OFFSET;
    if (y > 2 * step && y < 3 * step)
    {
        return dx * 255 * (y - 2 * step) / step;
    }
    else if (y >= 3 * step && y <= 5 * step)
    {
        return dx * 255;
    }
    else if (y > 5 * step)
    {
        return dx * 255 * (6 * step - y) / step;
    }
    else
    {
        return 0;
    }
}
