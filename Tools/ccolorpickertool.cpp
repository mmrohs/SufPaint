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

/*virtual*/ void CColorPickerTool::ProcessMousePressEvent(QPoint pos, QMouseEvent* pEvent)
{
    QImage* pImage = GetImage();
    if (pImage != NULL && pImage->rect().contains(pos))
    {
        QColor color = pImage->pixelColor(pos);
        CColorManager::GetColorManager()->SetForegroundColor(color);
    }
}
