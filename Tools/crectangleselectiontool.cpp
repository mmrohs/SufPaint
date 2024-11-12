#include "crectangleselectiontool.h"
#include "../Management/cselectionmanager.h"
#include "../Widgets/cimageview.h"


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

/*virtual*/ void CRectangleSelectionTool::ProcessMousePressEvent(QMouseEvent* pEvent)
{
    QImage* pImage = GetImage();
    if (pImage != NULL)
    {
        QPoint imagePos = GetImagePos(pEvent, true);
        if (pImage->rect().contains(imagePos))
        {
            CRectangleSelection* pSelection = new CRectangleSelection();
            pSelection->AddCoordinate(imagePos);
            CSelectionManager::GetSelectionManager()->SetSelection(pSelection);
        }
    }
}

/*virtual*/ void CRectangleSelectionTool::ProcessMouseReleaseEvent(QMouseEvent* pEvent)
{
    CSelectionManager::GetSelectionManager()->ClearSelection();
}

/*virtual*/ void CRectangleSelectionTool::ProcessMouseMoveEvent(QMouseEvent* pEvent)
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
