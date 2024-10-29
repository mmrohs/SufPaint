#include "ccolorpalettewidget.h"
#include <QPainter>
#include <QPen>
#include <QMouseEvent>


CColorPaletteWidget::CColorPaletteWidget(QWidget *parent)
    : QWidget{parent},
    m_pImage(NULL), m_selPoint(0, 0)
{
}

CColorPaletteWidget::~CColorPaletteWidget()
{
    if (m_pImage != NULL)
    {
        delete m_pImage;
    }
}

/*virtual*/ void CColorPaletteWidget::paintEvent(QPaintEvent* pEvent)
{
    static const QPen BPEN = QPen(QBrush(Qt::black), 3);
    static const QPen WPEN = QPen(QBrush(Qt::white), 1);

    // draw the pattern image
    QImage* pImage = GetPatternImage();
    QPainter paint;
    paint.begin(this);
    paint.drawImage(QPoint(0,0), *pImage);
    if (!m_selPoint.isNull())
    {
        paint.setPen(WPEN);
        paint.drawRect(QRect(m_selPoint.x() - 1, m_selPoint.y() - 1, 3, 3));
    }
    paint.end();
}

/*virtual*/ void CColorPaletteWidget::mousePressEvent(QMouseEvent* pEvent)
{
    QPointF posF = pEvent->position();
    m_selPoint = QPoint(posF.x(), posF.y());
    if (rect().contains(m_selPoint))
    {
        QPoint& p = m_selPoint;
        int r = CalcRed(p.x(), p.y());
        int g = CalcGreen(p.x(), p.y());
        int b = CalcBlue(p.x(), p.y());
        emit ColorPicked(QColor(r, g, b, 255));
    }
}

QSize CColorPaletteWidget::GetPatternSize() const
{
    return QSize(width(), height());
}

QImage* CColorPaletteWidget::GetPatternImage()
{
    if (m_pImage == NULL || m_pImage->size() != GetPatternSize())
    {
        GeneratePatternImage();
    }
    return m_pImage;
}

void CColorPaletteWidget::GeneratePatternImage()
{
    if (m_pImage != NULL)
    {
        delete m_pImage;
        m_pImage = NULL;
        m_selPoint = QPoint(0,0);
    }

    m_pImage = new QImage(GetPatternSize(), QImage::Format_ARGB32);

    for (int y = 0; y < m_pImage->height(); ++y)
    {
        QRgb* pLine = reinterpret_cast<QRgb*>(m_pImage->scanLine(y));
        if (pLine == NULL)
            continue;

        for (int x = 0; x < m_pImage->width(); ++x)
        {
            int r = CalcRed(x,y);
            int g = CalcGreen(x,y);
            int b = CalcBlue(x,y);
            pLine[x] = qRgba(r, g, b, 255);
        }
    }
}

int CColorPaletteWidget::CalcRed(int x, int y) const
{
    static const int OFFSET = 10; // offset for gray values bar
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

int CColorPaletteWidget::CalcGreen(int x, int y) const
{
    static const int OFFSET = 10; // offset for gray values bar
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

int CColorPaletteWidget::CalcBlue(int x, int y) const
{
    static const int OFFSET = 10; // offset for gray values bar
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
