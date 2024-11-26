#include "crectangleselectiontool.h"
#include "../Management/cselectionmanager.h"


CRectangleSelectionTool::CRectangleSelectionTool()
    : CTool(EnumTools::ToolRectSelect)
{
}

/*virtual*/ QIcon CRectangleSelectionTool::GetToolIcon() const
{
    QIcon icon("Icons/RectSelection.png");
    icon.addFile("Icons/RectSelection_Disabled.png", QSize(), QIcon::Mode::Disabled);
    return icon;
}

/*virtual*/ QString CRectangleSelectionTool::GetToolName() const
{
    return "Rectangle Select";
}

/*virtual*/ QString CRectangleSelectionTool::GetTooltip() const
{
    return "Select a rectangular area";
}

/*virtual*/ QString CRectangleSelectionTool::GetStatusText() const
{
    QString statustext = GetToolName();
    CSelection* pSelection = CSelectionManager::GetSelectionManager()->GetSelection();
    if (pSelection != NULL)
    {
        QRect rect = pSelection->GetBoundingRect();
        int width = abs(rect.width());
        int height = abs(rect.height());
        statustext += QString(" (Selection: %1 x %2 pixels)").arg(width).arg(height);
    }
    return statustext;
}

void CRectangleSelectionTool::ProcessMouseLPressEvent(QMouseEvent* pEvent)
{
    QPoint imgPos = GetMouseCoordinateFromEvent(pEvent);
    if (imgPos == QPoint(-1,-1))
        return;

    CRectangleSelection* pSelection = new CRectangleSelection();
    pSelection->AddCoordinate(imgPos);
    CSelectionManager::GetSelectionManager()->SetSelection(pSelection);
}

void CRectangleSelectionTool::ProcessMouseLReleaseEvent(QMouseEvent* pEvent)
{
    ProcessMouseLMoveEvent(pEvent);
}

void CRectangleSelectionTool::ProcessMouseLMoveEvent(QMouseEvent* pEvent)
{
    QPoint imgPos = GetMouseCoordinateFromEvent(pEvent);
    if (imgPos == QPoint(-1,-1))
        return;

    CSelection* pSelection = CSelectionManager::GetSelectionManager()->GetSelection();
    if (pSelection != NULL)
        pSelection->AddCoordinate(imgPos);
    CSelectionManager::GetSelectionManager()->SetSelection(pSelection);
}

void CRectangleSelectionTool::ProcessMouseRPressEvent(QMouseEvent* pEvent)
{
    CSelectionManager::GetSelectionManager()->ClearSelection();
}
