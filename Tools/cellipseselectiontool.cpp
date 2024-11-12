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

/*virtual*/ void CEllipseSelectionTool::ProcessMousePressEvent(QMouseEvent* pEvent)
{
    QImage* pImage = GetImage();
    if (pImage != NULL)
    {
        QPoint imagePos = GetImagePos(pEvent, true);
        if (pImage->rect().contains(imagePos))
        {
            CEllipticSelection* pSelection = new CEllipticSelection();
            pSelection->AddCoordinate(imagePos);
            CSelectionManager::GetSelectionManager()->SetSelection(pSelection);
        }
    }
}

/*virtual*/ void CEllipseSelectionTool::ProcessMouseReleaseEvent(QMouseEvent* pEvent)
{
    CSelectionManager::GetSelectionManager()->ClearSelection();
}

/*virtual*/ void CEllipseSelectionTool::ProcessMouseMoveEvent(QMouseEvent* pEvent)
{
    QImage* pImage = GetImage();
    if (pImage != NULL)
    {
        QPoint imagePos = GetImagePos(pEvent, true);
        if (pImage->rect().contains(imagePos))
        {
            CSelection* pSelection = CSelectionManager::GetSelectionManager()->GetSelection();
            if (pSelection != NULL)
                pSelection->AddCoordinate(imagePos);
            CSelectionManager::GetSelectionManager()->SetSelection(pSelection);
        }
    }
}
