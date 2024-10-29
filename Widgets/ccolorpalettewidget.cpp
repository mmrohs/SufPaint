#include "ccolorpalettewidget.h"
#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include "../Misc/ccolorpatternimage.h"


CColorPaletteWidget::CColorPaletteWidget(QWidget *parent)
    : QWidget{parent},
    m_pImage(NULL), m_selPoint(0, 0)
{
    setMouseTracking(false);
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
    QWidget::mousePressEvent(pEvent);
    mouseMoveEvent(pEvent);
}

/*virtual*/ void CColorPaletteWidget::mouseMoveEvent(QMouseEvent* pEvent)
{
    QPoint pos(pEvent->position().x(), pEvent->position().y());
    m_selPoint = pos;
    PickColorFromImage();
}

QSize CColorPaletteWidget::GetPatternSize() const
{
    return QSize(width(), height());
}

QImage* CColorPaletteWidget::GetPatternImage()
{
    if (m_pImage == NULL || m_pImage->size() != GetPatternSize())
    {
        delete m_pImage;
        m_pImage = new CColorPatternImage(GetPatternSize());
        m_selPoint = QPoint(0,0);
    }
    return m_pImage;
}

void CColorPaletteWidget::PickColorFromImage()
{
    if (m_pImage != NULL && rect().contains(m_selPoint))
    {
        QColor color = m_pImage->GetColorFromPos(m_selPoint);
        emit ColorPicked(color);
    }
}
