#include "cpantool.h"
#include "../Management/CImageViewManager.h"


CPanTool::CPanTool()
    : CTool(EnumTools::Pan)
{
}

/*virtual*/ QIcon CPanTool::GetToolIcon() const
{
    QIcon icon("Icons/Pan.png");
    icon.addFile("Icons/Pan_Disabled.png", QSize(), QIcon::Mode::Disabled);
    return icon;
}

/*virtual*/ QString CPanTool::GetToolName() const
{
    return "Pan";
}

/*virtual*/ QString CPanTool::GetTooltip() const
{
    return "Move the image view";
}

void CPanTool::ProcessMouseLPressEvent(QMouseEvent* pEvent)
{
    QPoint imgPos = GetMouseCoordinateFromEvent(pEvent);
    if (imgPos != QPoint(-1,-1))
    {
        m_startPos = imgPos;
    }
}

void CPanTool::ProcessMouseLMoveEvent(QMouseEvent* pEvent)
{
    QPoint imgPos = GetMouseCoordinateFromEvent(pEvent);
    if (imgPos != QPoint(-1,-1))
    {
        m_endPos = imgPos;
        if (m_startPos != m_endPos)
        {
            MoveImageView();
            m_startPos = m_endPos;
        }
    }
}

void CPanTool::MoveImageView()
{
    CImageViewManager* pIVM = CImageViewManager::GetImageViewManager();
    if (pIVM != NULL)
    {
        QPoint distance = m_endPos - m_startPos;
        pIVM->MoveView(distance);
    }
}
