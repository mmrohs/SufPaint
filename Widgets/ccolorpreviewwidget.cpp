#include "ccolorpreviewwidget.h"
#include <QPen>
#include <QPainter>
#include <QMouseEvent>
#include "../Misc/debugtools.h"
#include "../Management/ccolormanager.h"

// constants for the preview rects
#define TL QPoint(4, 10)        // top-left corner
#define DIST 10                 // distance between rects
#define SIZE 28                 // size of the rects
#define GAP 3                   // border gap


CColorPreviewWidget::CColorPreviewWidget(QWidget *parent)
    : QWidget{parent}
{
    ColorChanged();
}

void CColorPreviewWidget::ColorChanged()
{
    CColorManager* pColorManager = CColorManager::GetColorManager();
    m_foregroundColor = pColorManager->GetForegroundColor();
    m_backgroundColor = pColorManager->GetBackgroundColor();
    update();
}

/*virtual*/ void CColorPreviewWidget::paintEvent(QPaintEvent* pEvent)
{
    // Draw color filled rects for the foreground and background color
    static const QRect rectB(TL.x() + DIST, TL.y(), SIZE, SIZE);
    static const QRect rectF(TL.x(), TL.y() + DIST, SIZE, SIZE);
    DrawColorRect(rectB, m_backgroundColor);
    DrawColorRect(rectF, m_foregroundColor);

    // Save the bounding rectangle for the switch button
    m_rectFB = rectB.united(rectF);

#ifdef QT_DEBUG
    DebugShowWidgetBorders(this);
#endif
}

/*virtual*/ void CColorPreviewWidget::mousePressEvent(QMouseEvent* pEvent)
{
    QPointF pos = pEvent->position();
    QPoint mousePos(pos.x(), pos.y());
    if (m_rectFB.contains(mousePos))
    {
        CColorManager* pColorManager = CColorManager::GetColorManager();
        pColorManager->SwitchColors();
    }
}

/* Draws a color filled rect with a black border
 */
void CColorPreviewWidget::DrawColorRect(QRect rect, QColor color)
{
    static const QPen BPEN = QPen(QBrush(Qt::black), 3, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
    static const QPen WPEN = QPen(QBrush(Qt::white), 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);

    // calculate border rects
    QRect rectOuter(rect.x() - GAP, rect.y() - GAP, rect.width() + 2 * GAP, rect.height() + 2 * GAP);
    QRect rectInner(rect.x() - GAP + 2, rect.y() - GAP + 2, rect.width() + 2 * GAP - 4, rect.height() + 2 * GAP - 4);

    // draw border and selected color rects
    QPainter paint;
    paint.begin(this);
    paint.setPen(BPEN);
    paint.drawRect(rectOuter);
    paint.setPen(WPEN);
    paint.drawRect(rectInner);
    paint.fillRect(rect, QBrush(color));
    paint.end();
}
