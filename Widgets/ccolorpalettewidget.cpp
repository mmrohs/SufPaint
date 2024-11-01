#include "ccolorpalettewidget.h"
#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include "../Misc/ccolorpatternimage.h"
#include "../Misc/debugtools.h"
#include "../Management/ccolormanager.h"


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

void CColorPaletteWidget::ColorChanged()
{
    QColor color = CColorManager::GetColorManager()->GetForegroundColor();
    if (color != m_color)
    {
        m_selPoint = QPoint(0,0);
    }
    // to do
}

/*virtual*/ void CColorPaletteWidget::paintEvent(QPaintEvent* pEvent)
{
    // draw the pattern image
    QPainter paint;
    paint.begin(this);
    paint.drawImage(QPoint(0,0), *GetPatternImage());
    if (!m_selPoint.isNull())
    {
        static const QPen WPEN = QPen(QBrush(Qt::white), 1);
        paint.setPen(WPEN);
        paint.drawRect(QRect(m_selPoint.x() - 1, m_selPoint.y() - 1, 3, 3));
    }
    paint.end();

#ifdef QT_DEBUG
    DebugShowWidgetBorders(this);
#endif
}

/*virtual*/ void CColorPaletteWidget::mousePressEvent(QMouseEvent* pEvent)
{
    QWidget::mousePressEvent(pEvent);
    mouseMoveEvent(pEvent);
}

/*virtual*/ void CColorPaletteWidget::mouseMoveEvent(QMouseEvent* pEvent)
{
    if (m_pImage == NULL)
        return;

    QPointF posF = pEvent->position();
    QPoint pos(posF.x(), posF.y());
    if (!rect().contains(pos))
    {
        pos.setX(__max(pos.x(), 0));
        pos.setX(__min(pos.x(), rect().width()));
        pos.setY(__max(pos.y(), 0));
        pos.setY(__min(pos.y(), rect().height()));
        posF = pos;
    }
    m_selPoint = pos;
    m_color = m_pImage->GetColorFromPos(posF);
    CColorManager::GetColorManager()->SetForegroundColor(m_color, true);
    update();
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
        m_color = Qt::black;
    }
    return m_pImage;
}
