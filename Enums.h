#ifndef ENUMS_H
#define ENUMS_H


// Available menu actions
enum EnumActions : int
{
    ActionInvalid = -1,
    ActionDefault = 0,
    ActionSeparator = 1,

    // CFileMenu
    ActionFileNew = 10,        // Open a new file
    ActionFileOpen,            // Open an existing file
    ActionFileClose,           // Close file
    ActionFileSave,            // Save file
    ActionFileSaveAs,          // Save file in different format
    ActionFileQuit,            // Quit the application

    // CEditMenu
    ActionEditUndo,            // Undo the last action
    ActionEditRedo,            // Redo the last undone action
    ActionEditCopy,            // Copy the current selection
    ActionEditPaste,           // Paste the copied selection
    ActionEditCut,             // Cut the current selection

    // CViewMenu
    ActionViewZoomIn,          // Zoom into the image
    ActionViewZoomOut,         // Zoom out of the image
    ActionViewOrigSize,        // Reset zoom to original size (100%)

    // CImageMenu
    ActionImageResize,         // Resize the image
    ActionImageResizeCanvas,   // Resize the canvas
    ActionImageRotate90C,      // Rotate 90° clockwise
    ActionImageRotate90CC,     // Rotate 90° counter-clockwise
    ActionImageRotate180,      // Rotate 180°
    ActionImageMirrorHor,      // Mirror horizontally
    ActionImageMirrorVer,      // Mirror vertically

    // CAdjustmentMenu
    ActionAdjustInvert,         // Invert colors of the image
    ActionAdjustGrayscale,      // Transform image colors to grayscale
    ActionAdjustSepia,          // Transform image colors to sepia color scale

    // CHelpMenu
    ActionHelpInfo,            // show info dialog

    // to do

    ActionEnd                  // max value
};


// Available tools
enum EnumTools : int
{
    ToolInvalid = -1,
    ToolNone = 0,               // no tool selected (default)

    ToolColorPicker,            // color picker / color pipette
    ToolBrush,                  // drawing with a brush
    ToolPencil,                 // drawing with a pencil
    ToolBucket                  // fill areas with a color
};


// anchor positions
enum EnumAnchors : int
{
    Invalid = -1,
    Center = 0,
    TopLeft = 1,
    Top,
    TopRight,
    Right,
    BottomRight,
    Bottom,
    BottomLeft,
    Left
};

#endif // ENUMS_H
