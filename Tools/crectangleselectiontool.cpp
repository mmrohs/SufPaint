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

/*virtual*/ void CRectangleSelectionTool::ProcessMousePressEvent(QMouseEvent* pEvent, CImageView* pView)
{
    QImage* pImage = GetImage();
    if (pImage != NULL)
    {
        QPoint widgetPos (pEvent->position().x(), pEvent->position().y());
        QPoint imagePos = pView->GetTrafo()->TransformWidgetToImage(widgetPos);
        if (pImage->rect().contains(imagePos))
        {
            m_selectionRect = QRect(imagePos, QSize(1,1));
            CSelection selection;
            selection.SetRectangleSelection(m_selectionRect);
            CSelectionManager::GetSelectionManager()->SetSelection(selection);
        }
    }
}

/*virtual*/ void CRectangleSelectionTool::ProcessMouseReleaseEvent(QMouseEvent* pEvent, CImageView* pView)
{
    m_selectionRect = QRect();
    CSelectionManager::GetSelectionManager()->ClearSelection();
}

/*virtual*/ void CRectangleSelectionTool::ProcessMouseMoveEvent(QMouseEvent* pEvent, CImageView* pView)
{
    QImage* pImage = GetImage();
    if (pImage != NULL)
    {
        QPoint widgetPos (pEvent->position().x(), pEvent->position().y());
        QPoint imagePos = pView->GetTrafo()->TransformWidgetToImage(widgetPos);
        if (pImage->rect().contains(imagePos))
        {
            m_selectionRect |= QRect(imagePos, QSize(1,1));
            CSelection selection;
            selection.SetRectangleSelection(m_selectionRect);
            CSelectionManager::GetSelectionManager()->SetSelection(selection);
        }
    }
}
