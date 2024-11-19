#include "cellipseselectiontool.h"
#include "../Management/cselectionmanager.h"


CEllipseSelectionTool::CEllipseSelectionTool()
    : CTool(EnumTools::ToolEllipseSelect)
{
}

/*virtual*/ QString CEllipseSelectionTool::GetToolName()
{
    return "Ellipse Select";
}

/*virtual*/ QString CEllipseSelectionTool::GetTooltip()
{
    return "Select an elliptic area";
}

/*virtual*/ QIcon CEllipseSelectionTool::GetToolIcon()
{
    QIcon icon("Icons/EllipseSelection.png");
    icon.addFile("Icons/EllipseSelection_Disabled.png", QSize(), QIcon::Mode::Disabled);
    return icon;
}

/*virtual*/ void CEllipseSelectionTool::ProcessMouseLPressEvent(QMouseEvent* pEvent)
{
    QPoint imgPos = GetMouseCoordinateFromEvent(pEvent);
    if (imgPos == QPoint(-1,-1))
        return;

    CEllipticSelection* pSelection = new CEllipticSelection();
    pSelection->AddCoordinate(imgPos);
    CSelectionManager::GetSelectionManager()->SetSelection(pSelection);
}

/*virtual*/ void CEllipseSelectionTool::ProcessMouseLReleaseEvent(QMouseEvent* pEvent)
{
    ProcessMouseLMoveEvent(pEvent);
}

/*virtual*/ void CEllipseSelectionTool::ProcessMouseLMoveEvent(QMouseEvent* pEvent)
{
    QPoint imgPos = GetMouseCoordinateFromEvent(pEvent);
    if (imgPos == QPoint(-1,-1))
        return;

    CSelection* pSelection = CSelectionManager::GetSelectionManager()->GetSelection();
    if (pSelection != NULL)
        pSelection->AddCoordinate(imgPos);
    CSelectionManager::GetSelectionManager()->SetSelection(pSelection);
}

void CEllipseSelectionTool::ProcessMouseRPressEvent(QMouseEvent* pEvent)
{
    CSelectionManager::GetSelectionManager()->ClearSelection();
}
