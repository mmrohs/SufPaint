#include "ccolorpickertool.h"
#include "../Management/ccolormanager.h"


CColorPickerTool::CColorPickerTool()
    : CTool(EnumTools::ToolColorPicker)
{
}

/*virtual*/ QIcon CColorPickerTool::GetToolIcon() const
{
    QIcon icon("Icons/Pipette.png");
    icon.addFile("Icons/Pipette_Disabled.png", QSize(), QIcon::Mode::Disabled);
    return icon;
}

/*virtual*/ QString CColorPickerTool::GetToolName() const
{
    return "Color Picker";
}

/*virtual*/ QString CColorPickerTool::GetTooltip() const
{
    return "Pick a color from image";
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
