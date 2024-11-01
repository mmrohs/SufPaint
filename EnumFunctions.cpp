#include "EnumFunctions.h"
#include <QObject>


QString GetActionName(EnumActions e)
{
    switch (e)
    {
    case ActionFileNew:             return QObject::tr("&New");
    case ActionFileOpen:            return QObject::tr("&Open");
    case ActionFileClose:           return QObject::tr("&Close");
    case ActionFileSave:            return QObject::tr("&Save");
    case ActionFileSaveAs:          return QObject::tr("Save &As");
    case ActionFileQuit:            return QObject::tr("&Quit");
    //---------------------
    case ActionEditUndo:            return QObject::tr("&Undo");
    case ActionEditRedo:            return QObject::tr("&Redo");
    case ActionEditCopy:            return QObject::tr("&Copy");
    case ActionEditPaste:           return QObject::tr("&Paste");
    case ActionEditCut:             return QObject::tr("Cu&t");
    //---------------------
    case ActionViewZoomIn:          return QObject::tr("Zoom &in");
    case ActionViewZoomOut:         return QObject::tr("Zoom &out");
    case ActionViewOrigSize:        return QObject::tr("O&riginal size");
    //---------------------
    case ActionImageResize:         return QObject::tr("Res&ize");
    case ActionImageResizeCanvas:   return QObject::tr("Resize &canvas");
    case ActionImageRotate90C:      return QObject::tr("&Rotate by 90° clockwise");
    case ActionImageRotate90CC:     return QObject::tr("R&otate by 90° counter-clockwise");
    case ActionImageRotate180:      return QObject::tr("Ro&tate by 180°");
    case ActionImageMirrorHor:      return QObject::tr("Mirror &horizontally");
    case ActionImageMirrorVer:      return QObject::tr("Mirror &vertically");
    //---------------------
    case ActionAdjustInvert:        return QObject::tr("&Invert Colors");
    case ActionAdjustGrayscale:     return QObject::tr("&Grayscale");
    case ActionAdjustSepia:         return QObject::tr("&Sepia");
    //---------------------
    case ActionHelpInfo:            return QObject::tr("&Info");
    //---------------------
    default:                        return QObject::tr("error: missing name");
    }
    return "";
}

QKeySequence GetActionShortcut(EnumActions e)
{
    switch (e)
    {
    case ActionFileNew:             return QKeySequence::New;
    case ActionFileOpen:            return QKeySequence::Open;
    case ActionFileClose:           return QKeySequence::Close;
    case ActionFileSave:            return QKeySequence::Save;
    case ActionFileSaveAs:          return QKeySequence::SaveAs;
    case ActionFileQuit:            return QKeySequence::Quit;
    //---------------------
    case ActionEditUndo:            return QKeySequence::Undo;
    case ActionEditRedo:            return QKeySequence::Redo;
    case ActionEditCopy:            return QKeySequence::Copy;
    case ActionEditPaste:           return QKeySequence::Paste;
    case ActionEditCut:             return QKeySequence::Cut;
    //---------------------
    case ActionViewZoomIn:          return QKeySequence::ZoomIn;
    case ActionViewZoomOut:         return QKeySequence::ZoomOut;
    case ActionViewOrigSize:        return QKeySequence::FullScreen;
    //---------------------
    case ActionImageResize:         return QKeySequence(Qt::CTRL | Qt::ALT | Qt::Key_I);
    case ActionImageResizeCanvas:   return QKeySequence(Qt::CTRL | Qt::ALT | Qt::Key_C);
    case ActionImageRotate90C:      return QKeySequence(Qt::CTRL | Qt::Key_H);
    case ActionImageRotate90CC:     return QKeySequence(Qt::CTRL | Qt::Key_G);
    case ActionImageRotate180:      return QKeySequence(Qt::CTRL | Qt::Key_J);
    case ActionImageMirrorHor:      return QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_H);
    case ActionImageMirrorVer:      return QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_V);
    //---------------------
    case ActionAdjustInvert:        return QKeySequence::UnknownKey;
    case ActionAdjustGrayscale:     return QKeySequence::UnknownKey;
    case ActionAdjustSepia:         return QKeySequence::UnknownKey;
    //---------------------
    case ActionHelpInfo:            return QKeySequence::WhatsThis;
    //---------------------
    default:                        return QKeySequence::UnknownKey;
    }
}

QIcon GetActionIcon(EnumActions e)
{
    switch (e)
    {
    case ActionFileNew:             return QIcon::fromTheme(QIcon::ThemeIcon::DocumentNew);
    case ActionFileOpen:            return QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen);
    case ActionFileClose:           return QIcon::fromTheme(QIcon::ThemeIcon::MediaEject);
    case ActionFileSave:            return QIcon::fromTheme(QIcon::ThemeIcon::DocumentSave);
    case ActionFileSaveAs:          return QIcon::fromTheme(QIcon::ThemeIcon::DocumentSaveAs);
    case ActionFileQuit:            return QIcon::fromTheme(QIcon::ThemeIcon::WindowClose);
    //---------------------
    case ActionEditUndo:            return QIcon::fromTheme(QIcon::ThemeIcon::EditUndo);
    case ActionEditRedo:            return QIcon::fromTheme(QIcon::ThemeIcon::EditRedo);
    case ActionEditCopy:            return QIcon::fromTheme(QIcon::ThemeIcon::EditCopy);
    case ActionEditPaste:           return QIcon::fromTheme(QIcon::ThemeIcon::EditPaste);
    case ActionEditCut:             return QIcon::fromTheme(QIcon::ThemeIcon::EditCut);
    //---------------------
    case ActionViewZoomIn:          return QIcon::fromTheme(QIcon::ThemeIcon::ZoomIn);
    case ActionViewZoomOut:         return QIcon::fromTheme(QIcon::ThemeIcon::ZoomOut);
    case ActionViewOrigSize:        return QIcon::fromTheme(QIcon::ThemeIcon::ZoomFitBest);
    //---------------------
    case ActionImageResize:         return QIcon::fromTheme(QIcon::ThemeIcon::WindowNew);
    case ActionImageResizeCanvas:   return QIcon::fromTheme(QIcon::ThemeIcon::WindowNew);
    case ActionImageRotate90C:      return QIcon::fromTheme(QIcon::ThemeIcon::ObjectRotateRight);
    case ActionImageRotate90CC:     return QIcon::fromTheme(QIcon::ThemeIcon::ObjectRotateLeft);
    case ActionImageRotate180:      return QIcon();
    case ActionImageMirrorHor:      return QIcon();
    case ActionImageMirrorVer:      return QIcon();
    //---------------------
    case ActionAdjustInvert:        return QIcon();
    case ActionAdjustGrayscale:     return QIcon();
    case ActionAdjustSepia:         return QIcon();
    //---------------------
    case ActionHelpInfo:            return QIcon::fromTheme(QIcon::ThemeIcon::DialogInformation);
    //---------------------
    default:                        return QIcon();
    }
}

