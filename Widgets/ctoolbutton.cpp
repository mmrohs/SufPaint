#include "ctoolbutton.h"
#include <QPainter>
#include <QPaintEvent>
#include "../EnumFunctions.h"
#include "../Management/ctoolmanager.h"

#define ICON_SIZE 32


CToolButton::CToolButton(EnumTools tool, QWidget* parent /*= nullptr*/)
    : QToolButton(parent),
    m_tool(tool), m_bActive(false)
{
    SetIcon();
    SetTooltip();
}

void CToolButton::SetActive(bool bActive)
{
    bool bUpdate = m_bActive != bActive;
    m_bActive = bActive;
    if (bUpdate)
        update();
}

bool CToolButton::IsActive() const
{
    return m_bActive;
}

void CToolButton::ToolChanged()
{
    CToolManager* pToolManager = CToolManager::GetToolManager();
    if (pToolManager != NULL)
    {
        bool bActive = pToolManager->IsActiveTool(m_tool);
        SetActive(bActive);
    }
}

void CToolButton::SetIcon()
{
    QIcon icon = GetToolIcon(m_tool);
    setIcon(icon);
    setIconSize(QSize(ICON_SIZE, ICON_SIZE));
}

void CToolButton::SetTooltip()
{
    QString tooltip = GetToolTooltip(m_tool);
    setToolTip(tooltip);
}

/*virtual*/ void CToolButton::paintEvent(QPaintEvent* pEvent)
{
    QToolButton::paintEvent(pEvent);

    if (m_bActive)
    {
        // draw a blue rectangle around the icon
        static const QPen PEN(QBrush(Qt::darkBlue), 3, Qt::SolidLine);
        QPainter paint;
        paint.begin(this);
        //paint.setClipRect(pEvent->rect());
        paint.setPen(PEN);
        paint.drawRect(QRect(2,2,34,33));
        paint.end();
    }
}

/*virtual*/ void CToolButton::mousePressEvent(QMouseEvent* pEvent)
{
    Q_ASSERT(isEnabled());

    CToolManager* pToolManager = CToolManager::GetToolManager();
    if (pToolManager != NULL)
    {
        pToolManager->SetActiveTool(m_tool);
    }
}
