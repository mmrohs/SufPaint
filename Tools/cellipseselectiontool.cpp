#include "cellipseselectiontool.h"
#include "../Management/cselectionmanager.h"


CEllipseSelectionTool::CEllipseSelectionTool()
    : CTool(EnumTools::ToolEllipseSelect)
{
}

/*virtual*/ QIcon CEllipseSelectionTool::GetToolIcon() const
{
    QIcon icon("Icons/EllipseSelection.png");
    icon.addFile("Icons/EllipseSelection_Disabled.png", QSize(), QIcon::Mode::Disabled);
    return icon;
}

/*virtual*/ QString CEllipseSelectionTool::GetToolName() const
{
    return "Ellipse Select";
}

/*virtual*/ QString CEllipseSelectionTool::GetTooltip() const
{
    return "Select an elliptic area";
}

/*virtual*/ QString CEllipseSelectionTool::GetStatusText() const
{
    QString statustext = GetToolName();
    CSelection* pSelection = CSelectionManager::GetSelectionManager()->GetSelection();
    if (pSelection != NULL)
    {
        QRect rect = pSelection->GetBoundingRect();
        statustext += QString(" (Bounding rect: %1 x %2 pixels)").arg(abs(rect.width())).arg(abs(rect.height()));
    }
    return statustext;
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
