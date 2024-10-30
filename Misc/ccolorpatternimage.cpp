#include "ccolorpatternimage.h"

#define OFFSET 6    // height of the gray scale at the top (-> offset for the color pattern below)


CColorPatternImage::CColorPatternImage(QSize size, Mode mode /*= Dark*/)
    : QImage(size, QImage::Format_ARGB32)
{
    SetStep();
    SetMode(mode);
}

CColorPatternImage::CColorPatternImage(int width, int height, Mode mode /*= Dark*/)
    : QImage(width, height, QImage::Format_ARGB32)
{
    SetStep();
    SetMode(mode);
}

void CColorPatternImage::SetStep()
{
    m_step = (height() - OFFSET) / 6.0;
}

void CColorPatternImage::SetMode(Mode mode)
{
    m_mode = mode;
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
    if (m_mode == Mode::Light && pos.y() >= OFFSET)
    {
        double w = width();
        r += 255 * (1.0 - pos.x() / w);
        g += 255 * (1.0 - pos.x() / w);
        b += 255 * (1.0 - pos.x() / w);
    }
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
    double x = pos.x();
    double y = pos.y();
    double dx = (double) x / width();   // 0.0...1.0

    if (y < OFFSET)
    {
        return dx * 255;
    }

    y -= OFFSET;
    if (y <= m_step || y >= 5 * m_step)
    {
        return dx * 255;
    }
    else if (y > m_step && y < 2 * m_step)
    {
        return dx * 255 * (2 * m_step - y) / m_step;
    }
    else if (y > 4 * m_step && y < 5 * m_step)
    {
        return dx * 255 * (y - 4 * m_step) / m_step;
    }
    else
    {
        return 0;
    }
}

int CColorPatternImage::CalcGreen(QPointF pos) const
{
    double x = pos.x();
    double y = pos.y();
    double dx = (double) x / width();   // 0.0...1.0

    if (y < OFFSET)
    {
        return dx * 255;
    }

    y -= OFFSET;
    if (y < m_step)
    {
        return dx * 255 * y / m_step;
    }
    else if (y >= m_step && y <= 3 * m_step)
    {
        return dx * 255;
    }
    else if (y > 3 * m_step && y < 4 * m_step)
    {
        return dx * 255 * (4 * m_step - y) / m_step;
    }
    else
    {
        return 0;
    }
}

int CColorPatternImage::CalcBlue(QPointF pos) const
{
    double x = pos.x();
    double y = pos.y();
    double dx = (double) x / width();   // 0.0...1.0

    if (y < OFFSET)
    {
        return dx * 255;
    }

    y -= OFFSET;
    if (y > 2 * m_step && y < 3 * m_step)
    {
        return dx * 255 * (y - 2 * m_step) / m_step;
    }
    else if (y >= 3 * m_step && y <= 5 * m_step)
    {
        return dx * 255;
    }
    else if (y > 5 * m_step)
    {
        return dx * 255 * (6 * m_step - y) / m_step;
    }
    else
    {
        return 0;
    }
}
