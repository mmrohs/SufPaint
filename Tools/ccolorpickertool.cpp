#include "ccolorpickertool.h"
#include "../Management/ccolormanager.h"


CColorPickerTool::CColorPickerTool()
    : CTool(EnumTools::ToolColorPicker)
{
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
