#include "ctool.h"
#include "../Management/cimagemanager.h"


CTool::CTool(EnumTools eTool)
    : m_eTool(eTool)
{
}

/*virtual*/ CTool::~CTool()
{
}

QString CTool::GetToolName() const
{
    return GetToolName(m_eTool);
}

EnumTools CTool::GetToolEnum() const
{
    return m_eTool;
}

QImage* CTool::GetImage() const
{
    CImageManager* pImageManager = CImageManager::GetImageManager();
    if (pImageManager != NULL)
    {
        return pImageManager->GetImage();
    }
    return NULL;
}

/*static*/ QString CTool::GetToolName(EnumTools e)
{
    switch (e)
    {
    case ToolNone:                  return "-";
    case ToolRectSelect:            return "Rectangle Select";
    case ToolColorPicker:           return "Color Picker";
    case ToolBrush:                 return "Brush";
    case ToolPencil:                return "Pencil";
    case ToolLine:                  return "Line Tool";
    case ToolBucket:                return "Paint Bucket";
    case ToolGradient:              return "Color Gradient";
    default:                        return "";
    }
}

/*static*/ QString CTool::GetTooltip(EnumTools tool)
{
    switch (tool)
    {
    case ToolRectSelect:            return "Select a rectangular area";
    case ToolColorPicker:           return "Pick a color from image";
    case ToolBrush:                 return "Draw with a brush";
    case ToolPencil:                return "Draw with a pencil";
    case ToolLine:                  return "Draw lines and splines";
    case ToolBucket:                return "Fill areas with a color";
    case ToolGradient:              return "Fill areas with a color gradient";
    default:                        return "";
    }
}

/*static*/ QIcon CTool::GetToolIcon(EnumTools tool)
{
    switch (tool)
    {
    case ToolRectSelect:
    {
        QIcon icon("Icons/RectSelection.png");
        icon.addFile("Icons/RectSelection_Disabled.png", QSize(), QIcon::Mode::Disabled);
        return icon;
    }
    case ToolColorPicker:
    {
        QIcon icon("Icons/Pipette.png");
        icon.addFile("Icons/Pipette_Disabled.png", QSize(), QIcon::Mode::Disabled);
        return icon;
    }
    case ToolBrush:
    {
        QIcon icon("Icons/Brush.png");
        icon.addFile("Icons/Brush_Disabled.png", QSize(), QIcon::Mode::Disabled);
        return icon;
    }
    case ToolPencil:
    {
        QIcon icon("Icons/Pencil.png");
        icon.addFile("Icons/Pencil_Disabled.png", QSize(), QIcon::Mode::Disabled);
        return icon;
    }
    case ToolLine:
    {
        QIcon icon("Icons/LineTool.png");
        icon.addFile("Icons/LineTool_Disabled.png", QSize(), QIcon::Mode::Disabled);
        return icon;
    }
    case ToolBucket:
    {
        QIcon icon("Icons/Bucket.png");
        icon.addFile("Icons/Bucket_Disabled.png", QSize(), QIcon::Mode::Disabled);
        return icon;
    }
    case ToolGradient:
    {
        QIcon icon("Icons/Gradient.png");
        icon.addFile("Icons/Gradient_Disabled.png", QSize(), QIcon::Mode::Disabled);
        return icon;
    }
    default:
        return QIcon();
    }
}
