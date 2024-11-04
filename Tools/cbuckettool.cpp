#include "cbuckettool.h"


CBucketTool::CBucketTool()
    : CTool(EnumTools::ToolBucket)
{
}

/*virtual*/ QString CBucketTool::GetToolName()
{
    return "Paint Bucket";
}

/*virtual*/ QString CBucketTool::GetTooltip()
{
    return "Fill areas with a color";
}

/*virtual*/ QIcon CBucketTool::GetToolIcon()
{
    QIcon icon("Icons/Bucket.png");
    icon.addFile("Icons/Bucket_Disabled.png", QSize(), QIcon::Mode::Disabled);
    return icon;
}

/*virtual*/ void CBucketTool::ProcessMousePressEvent(QPoint pos, QMouseEvent* pEvent)
{
    QImage* pImage = GetImage();
    if (pImage != NULL && pImage->rect().contains(pos))
    {
        // to do
    }
}