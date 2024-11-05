#include "ccolorpickertool.h"
#include "../Management/ccolormanager.h"
#include "../Widgets/cimageview.h"


CColorPickerTool::CColorPickerTool()
    : CTool(EnumTools::ToolColorPicker)
{
}

/*virtual*/ QString CColorPickerTool::GetToolName()
{
    return "Color Picker";
}

/*virtual*/ QString CColorPickerTool::GetTooltip()
{
    return "Pick a color from image";
}

/*virtual*/ QIcon CColorPickerTool::GetToolIcon()
{
    QIcon icon("Icons/Pipette.png");
    icon.addFile("Icons/Pipette_Disabled.png", QSize(), QIcon::Mode::Disabled);
    return icon;
}

/*virtual*/ void CColorPickerTool::ProcessMousePressEvent(QMouseEvent* pEvent, CImageView* pView)
{
    QImage* pImage = GetImage();
    if (pImage != NULL)
    {
        QPoint widgetPos (pEvent->position().x(), pEvent->position().y());
        QPoint imagePos = pView->GetTrafo()->TransformWidgetToImage(widgetPos);
        if (pImage->rect().contains(imagePos))
        {
            QColor color = pImage->pixelColor(imagePos);
            CColorManager::GetColorManager()->SetForegroundColor(color);
        }
    }
}
