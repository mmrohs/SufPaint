#include "ccolorrgbawidget.h"
#include <QGridLayout>
#include <QSpinBox>
#include <QLabel>
#include "../Misc/debugtools.h"

#define RGBAMIN 0
#define RGBAMAX 255
#define SPINMIN RGBAMIN
#define SPINMAX 999


CColorRgbaWidget::CColorRgbaWidget(QWidget *parent)
    : QWidget{parent}
{
    AddLayout();
    AddConnections();
}

void CColorRgbaWidget::AddLayout()
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
    pGridLayout->setColumnStretch(0, 1);
    pGridLayout->setColumnStretch(1, 4);
    pGridLayout->setHorizontalSpacing(4);
    pGridLayout->setVerticalSpacing(5);

    // add the spinboxes to the grid layout
    QString texts[] = {"R:", "G:", "B:", "A:"};
    for (int i = 0; i < 4; ++i)
    {
        pGridLayout->addWidget(new QLabel(texts[i]), i, 0);
        pGridLayout->addWidget(m_pSpinBoxes[i], i, 1);
    }

    setLayout(pGridLayout);
}

void CColorRgbaWidget::AddConnections()
{
    for (int i = 0; i < 4; ++i)
    {
        connect(m_pSpinBoxes[i], &QSpinBox::valueChanged, this, &CColorRgbaWidget::RgbaChanged);
    }
}

void CColorRgbaWidget::SetColor(QColor color)
{
    m_color = color;
    UpdateControls();
}

void CColorRgbaWidget::RgbaChanged()
{
    CheckRgbaValues();

    QColor color;
    color.setRed(m_pSpinBoxes[0]->value());
    color.setGreen(m_pSpinBoxes[1]->value());
    color.setBlue(m_pSpinBoxes[2]->value());
    color.setAlpha(m_pSpinBoxes[3]->value());
    m_color = color;
    update();

    emit ColorChanged(color);
}

/* Checks the RGBA-Spinboxes for invalid values outside of [0, 255]
 */
void CColorRgbaWidget::CheckRgbaValues()
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

void CColorRgbaWidget::UpdateControls()
{
    int rgba[] = {m_color.red(), m_color.green(), m_color.blue(), m_color.alpha()};
    for (int i = 0; i < 4; ++i)
    {
        QSignalBlocker blocker(m_pSpinBoxes[i]);
        m_pSpinBoxes[i]->setValue(rgba[i]);
    }
}

/*virtual*/ void CColorRgbaWidget::paintEvent(QPaintEvent* pEvent)
{
    QWidget::paintEvent(pEvent);

#ifdef QT_DEBUG
    DebugShowWidgetBorders(this);
#endif
}
