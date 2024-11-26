#include "EnumFunctions.h"
#include <QObject>
#include "Tools/ccolorpickertool.h"
#include "Tools/crectangleselectiontool.h"
#include "Tools/cellipseselectiontool.h"
#include "Tools/cbrushtool.h"
#include "Tools/cpenciltool.h"
#include "Tools/cbuckettool.h"
#include "Tools/cgradienttool.h"
#include "Tools/clinestool.h"
#include "Tools/cpantool.h"


QString GetActionName(EnumActions action)
{
    switch (action)
    {
    case FileNew:             return QObject::tr("&New");
    case FileOpen:            return QObject::tr("&Open");
    case FileClose:           return QObject::tr("&Close");
    case FileSave:            return QObject::tr("&Save");
    case FileSaveAs:          return QObject::tr("Save &As");
    case FileQuit:            return QObject::tr("&Quit");
    //---------------------
    case EditUndo:            return QObject::tr("&Undo");
    case EditRedo:            return QObject::tr("&Redo");
    case EditCopy:            return QObject::tr("&Copy");
    case EditPaste:           return QObject::tr("&Paste");
    case EditCut:             return QObject::tr("Cu&t");
    //---------------------
    case ViewZoomIn:          return QObject::tr("Zoom &in");
    case ViewZoomOut:         return QObject::tr("Zoom &out");
    case ViewOrigSize:        return QObject::tr("O&riginal size");
    //---------------------
    case ImageResize:         return QObject::tr("Res&ize");
    case ImageResizeCanvas:   return QObject::tr("Resize &canvas");
    case ImageCropSelection:  return QObject::tr("Crop to Selection");
    case ImageRotate90CC:     return QObject::tr("R&otate by 90° counter-clockwise");
    case ImageRotate90C:      return QObject::tr("&Rotate by 90° clockwise");
    case ImageRotate180:      return QObject::tr("Ro&tate by 180°");
    case ImageMirrorHor:      return QObject::tr("Mirror &horizontally");
    case ImageMirrorVer:      return QObject::tr("Mirror &vertically");
    //---------------------
    case AdjustInvert:        return QObject::tr("&Invert Colors");
    case AdjustGrayscale:     return QObject::tr("&Grayscale");
    case AdjustSepia:         return QObject::tr("&Sepia");
    //---------------------
    case HelpInfo:            return QObject::tr("&Info");
    //---------------------
    default:                  return QObject::tr("error: missing name");
    }
    return "";
}

QKeySequence GetActionShortcut(EnumActions action)
{
    switch (action)
    {
    case FileNew:             return QKeySequence::New;
    case FileOpen:            return QKeySequence::Open;
    case FileClose:           return QKeySequence::Close;
    case FileSave:            return QKeySequence::Save;
    case FileSaveAs:          return QKeySequence::SaveAs;
    case FileQuit:            return QKeySequence::Quit;
    //---------------------
    case EditUndo:            return QKeySequence::Undo;
    case EditRedo:            return QKeySequence::Redo;
    case EditCopy:            return QKeySequence::Copy;
    case EditPaste:           return QKeySequence::Paste;
    case EditCut:             return QKeySequence::Cut;
    //---------------------
    case ViewZoomIn:          return QKeySequence::ZoomIn;
    case ViewZoomOut:         return QKeySequence::ZoomOut;
    case ViewOrigSize:        return QKeySequence::FullScreen;
    //---------------------
    case ImageResize:         return QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_I);
    case ImageResizeCanvas:   return QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_C);
    case ImageCropSelection:  return QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_X);
    case ImageRotate90C:      return QKeySequence(Qt::CTRL | Qt::Key_H);
    case ImageRotate90CC:     return QKeySequence(Qt::CTRL | Qt::Key_G);
    case ImageRotate180:      return QKeySequence(Qt::CTRL | Qt::Key_J);
    case ImageMirrorHor:      return QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_H);
    case ImageMirrorVer:      return QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_V);
    //---------------------
    case AdjustInvert:        return QKeySequence::UnknownKey;
    case AdjustGrayscale:     return QKeySequence::UnknownKey;
    case AdjustSepia:         return QKeySequence::UnknownKey;
    //---------------------
    case HelpInfo:            return QKeySequence::WhatsThis;
    //---------------------
    default:                  return QKeySequence::UnknownKey;
    }
}

QIcon GetActionIcon(EnumActions action)
{
    switch (action)
    {
    case FileNew:             return QIcon::fromTheme(QIcon::ThemeIcon::DocumentNew);
    case FileOpen:            return QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen);
    case FileClose:           return QIcon::fromTheme(QIcon::ThemeIcon::MediaEject);
    case FileSave:            return QIcon::fromTheme(QIcon::ThemeIcon::DocumentSave);
    case FileSaveAs:          return QIcon::fromTheme(QIcon::ThemeIcon::DocumentSaveAs);
    case FileQuit:            return QIcon::fromTheme(QIcon::ThemeIcon::WindowClose);
    //---------------------
    case EditUndo:            return QIcon::fromTheme(QIcon::ThemeIcon::EditUndo);
    case EditRedo:            return QIcon::fromTheme(QIcon::ThemeIcon::EditRedo);
    case EditCopy:            return QIcon::fromTheme(QIcon::ThemeIcon::EditCopy);
    case EditPaste:           return QIcon::fromTheme(QIcon::ThemeIcon::EditPaste);
    case EditCut:             return QIcon::fromTheme(QIcon::ThemeIcon::EditCut);
    //---------------------
    case ViewZoomIn:          return QIcon::fromTheme(QIcon::ThemeIcon::ZoomIn);
    case ViewZoomOut:         return QIcon::fromTheme(QIcon::ThemeIcon::ZoomOut);
    case ViewOrigSize:        return QIcon::fromTheme(QIcon::ThemeIcon::ZoomFitBest);
    //---------------------
    case ImageResize:         return QIcon::fromTheme(QIcon::ThemeIcon::WindowNew);
    case ImageResizeCanvas:   return QIcon::fromTheme(QIcon::ThemeIcon::WindowNew);
    case ImageCropSelection:  return QIcon();
    case ImageRotate90C:      return QIcon::fromTheme(QIcon::ThemeIcon::ObjectRotateRight);
    case ImageRotate90CC:     return QIcon::fromTheme(QIcon::ThemeIcon::ObjectRotateLeft);
    case ImageRotate180:      return QIcon();
    case ImageMirrorHor:      return QIcon();
    case ImageMirrorVer:      return QIcon();
    //---------------------
    case AdjustInvert:        return QIcon();
    case AdjustGrayscale:     return QIcon();
    case AdjustSepia:         return QIcon();
    //---------------------
    case HelpInfo:            return QIcon::fromTheme(QIcon::ThemeIcon::DialogInformation);
    //---------------------
    default:                  return QIcon();
    }
}

CTool* GetNewTool(EnumTools tool)
{
    switch (tool)
    {
    case Pan:           return new CPanTool();
    case RectSelect:    return new CRectangleSelectionTool();
    case EllipseSelect: return new CEllipseSelectionTool();
    case ColorPicker:   return new CColorPickerTool();
    case Brush:         return new CBrushTool();
    case Pencil:        return new CPencilTool();
    case Bucket:        return new CBucketTool();
    case Gradient:      return new CGradientTool();
    case Line:          return new CLinesTool();
    default:            return NULL;
    }
}

QString GetToolName(EnumTools tool)
{
    CTool* pTool = GetNewTool(tool);
    if (pTool != NULL)
    {
        QString toolname = pTool->GetToolName();
        delete pTool;
        return toolname;
    }
    return "";
}

QString GetTooltip(EnumTools tool)
{
    CTool* pTool = GetNewTool(tool);
    if (pTool != NULL)
    {
        QString tooltip = pTool->GetTooltip();
        delete pTool;
        return tooltip;
    }
    return "";
}

QIcon GetToolIcon(EnumTools tool)
{
    CTool* pTool = GetNewTool(tool);
    if (pTool != NULL)
    {
        QIcon icon = pTool->GetToolIcon();
        delete pTool;
        return icon;
    }
    return QIcon();
}
