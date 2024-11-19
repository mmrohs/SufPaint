#include "ccolorpickertool.h"
#include "../Management/ccolormanager.h"


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

/*virtual*/ void CColorPickerTool::ProcessMouseLPressEvent(QMouseEvent* pEvent)
{
    QImage* pImage = GetImage();
    if (pImage != NULL)
    {
        QPoint imgPos = GetImagePos(pEvent, false);
        if (pImage->rect().contains(imgPos))
        {
            QColor color = pImage->pixelColor(imgPos);
            CColorManager::GetColorManager()->SetForegroundColor(color);
        }
    }
}
