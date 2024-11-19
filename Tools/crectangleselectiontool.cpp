#include "crectangleselectiontool.h"
#include "../Management/cselectionmanager.h"


CRectangleSelectionTool::CRectangleSelectionTool()
    : CTool(EnumTools::ToolRectSelect)
{
}

/*virtual*/ QString CRectangleSelectionTool::GetToolName()
{
    return "Rectangle Select";
}

/*virtual*/ QString CRectangleSelectionTool::GetTooltip()
{
    return "Select a rectangular area";
}

/*virtual*/ QIcon CRectangleSelectionTool::GetToolIcon()
{
    QIcon icon("Icons/RectSelection.png");
    icon.addFile("Icons/RectSelection_Disabled.png", QSize(), QIcon::Mode::Disabled);
    return icon;
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
