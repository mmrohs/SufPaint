#include "ccolorwidget.h"
#include <QLabel>
#include <QSpinBox>
#include <QGridLayout>
#include <QBoxLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QPen>

// fixed widget width
#define WIDTH 150
#define RGBAMIN 0
#define RGBAMAX 255
#define SPINMIN RGBAMIN
#define SPINMAX 999


CColorWidget::CColorWidget(QWidget* pParent)
    : QGroupBox(tr("Colors"), pParent)
{
    setMinimumWidth(WIDTH);
    setMaximumWidth(WIDTH);

    m_foregroundColor = Qt::black;
    m_backgroundColor = Qt::white;

    AddLayout();
    AddConnections();

    ColorPicked(Qt::black);
}

void CColorWidget::AddLayout()
{
    // create the spin boxes
    for (int i = 0; i < 4; ++i)
    {
        m_pSpinBoxes[i] = new QSpinBox(this);
        m_pSpinBoxes[i]->setMinimum(SPINMIN);
        m_pSpinBoxes[i]->setMaximum(SPINMAX);
    }

    // create the grid layout
    QGridLayout* pGridLayout = new QGridLayout();
    pGridLayout->setColumnStretch(0, 9);
    pGridLayout->setColumnStretch(1, 1);
    pGridLayout->setColumnStretch(2, 6);

    // add the spinboxes to the grid layout
    QString texts[] = {"R:", "G:", "B:", "A:"};
    for (int i = 0; i < 4; ++i)
    {
        pGridLayout->addItem(new QSpacerItem(1, 1), i, 0);
        pGridLayout->addWidget(new QLabel(texts[i]), i, 1);
        pGridLayout->addWidget(m_pSpinBoxes[i], i, 2);
    }

    QVBoxLayout* vbox = new QVBoxLayout();
    vbox->addLayout(pGridLayout, 1);
    vbox->addStretch(5);

    setLayout(vbox);
}

void CColorWidget::AddConnections()
{
    for (int i = 0; i < 4; ++i)
    {
        connect(m_pSpinBoxes[i], &QSpinBox::valueChanged, this, &CColorWidget::RgbaChanged);
    }
}

void CColorWidget::ColorPicked(QColor color)
{
    int rgba[] = {color.red(), color.green(), color.blue(), color.alpha()};
    for (int i = 0; i < 4; ++i)
    {
        QSignalBlocker blocker(m_pSpinBoxes[i]);
        m_pSpinBoxes[i]->setValue(rgba[i]);
    }
    m_foregroundColor = color;
    update();
}

void CColorWidget::RgbaChanged()
{
    CheckRgbaValues();

    QColor color;
    color.setRed(m_pSpinBoxes[0]->value());
    color.setGreen(m_pSpinBoxes[1]->value());
    color.setBlue(m_pSpinBoxes[2]->value());
    color.setAlpha(m_pSpinBoxes[3]->value());
    m_foregroundColor = color;
    update();
}

/* Checks the RGBA-Spinboxes for invalid values
 */
void CColorWidget::CheckRgbaValues()
{
    for (int i = 0; i < 4; ++i)
    {
        if (m_pSpinBoxes[i]->value() > RGBAMAX)
        {
            QSignalBlocker blocker(m_pSpinBoxes[i]);
            m_pSpinBoxes[i]->setValue(RGBAMAX);
        }
        else if (m_pSpinBoxes[i]->value() < RGBAMIN)
        {
            QSignalBlocker blocker(m_pSpinBoxes[i]);
            m_pSpinBoxes[i]->setValue(RGBAMIN);
        }
    }
}

/*virtual*/ void CColorWidget::paintEvent(QPaintEvent* pEvent)
{
    QGroupBox::paintEvent(pEvent);

    // Draw color filled rects for the foreground and background color
    static const int DIST = 10;
    static const int SIZE = 30;
    static const QPoint TL = QPoint(15, 30); // top-left corner
    static const QRect rectB(TL.x() + DIST, TL.y(), SIZE, SIZE);
    static const QRect rectF(TL.x(), TL.y() + DIST, SIZE, SIZE);
    DrawColorRect(rectB, m_backgroundColor);
    DrawColorRect(rectF, m_foregroundColor);

    // Save the bounding rectangle for the switch button
    m_rectFB = rectB.united(rectF);
}

/*virtual*/ void CColorWidget::mousePressEvent(QMouseEvent* pEvent)
{
    QPoint mousePos(pEvent->position().x(), pEvent->position().y());
    if (m_rectFB.contains(mousePos))
    {
        QColor backgroundColor = m_backgroundColor;
        m_backgroundColor = m_foregroundColor;
        ColorPicked(backgroundColor);
    }
}

/* Draws a color filled rect with a black border
 */
void CColorWidget::DrawColorRect(QRect rect, QColor color)
{
    static const int GAP = 3; // border gap
    static const QPen BPEN = QPen(QBrush(Qt::black), 3);
    static const QPen WPEN = QPen(QBrush(Qt::white), 2);

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
