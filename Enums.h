#ifndef ENUMS_H
#define ENUMS_H


// Available menu actions
enum EnumActions : int
{
    Invalid = -1,
    Default = 0,
    Separator = 1,

    // CFileMenu
    FileNew = 10,        // Open a new file
    FileOpen,            // Open an existing file
    FileClose,           // Close file
    FileSave,            // Save file
    FileSaveAs,          // Save file in different format
    FileQuit,            // Quit the application

    // CEditMenu
    EditUndo,            // Undo the last action
    EditRedo,            // Redo the last undone action
    EditCopy,            // Copy the current selection
    EditPaste,           // Paste the copied selection
    EditCut,             // Cut the current selection

    // CViewMenu
    ViewZoomIn,          // Zoom into the image
    ViewZoomOut,         // Zoom out of the image
    ViewOrigSize,        // Reset zoom to original size (100%)

    // CImageMenu
    ImageResize,         // Resize the image
    ImageResizeCanvas,   // Resize the canvas
    ImageCropSelection,  // Crop the image to the selection
    ImageRotate90C,      // Rotate 90° clockwise
    ImageRotate90CC,     // Rotate 90° counter-clockwise
    ImageRotate180,      // Rotate 180°
    ImageMirrorHor,      // Mirror horizontally
    ImageMirrorVer,      // Mirror vertically

    // CAdjustmentMenu
    AdjustInvert,         // Invert colors of the image
    AdjustGrayscale,      // Transform image colors to grayscale
    AdjustSepia,          // Transform image colors to sepia color scale

    // CHelpMenu
    HelpInfo,            // show info dialog

    // to do

    End                  // max value
};


// Available tools
enum EnumTools : int
{
    None = 0,               // no tool selected (default)
    RectSelect,             // select a rectangular area
    EllipseSelect,          // select an elliptic area
    ColorPicker,            // color picker / color pipette
    Brush,                  // drawing with a brush
    Pencil,                 // drawing with a pencil
    Line,                   // drawing lines
    Bucket,                 // fill areas with a color
    Gradient                // color gradient
};


// anchor positions
enum EnumAnchors : int
{
    Center = 0,
    TopLeft,
    Top,
    TopRight,
    Right,
    BottomRight,
    Bottom,
    BottomLeft,
    Left
};

#endif // ENUMS_H
