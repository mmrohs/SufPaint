#include "cbuckettool.h"


CBucketTool::CBucketTool()
    : CTool(EnumTools::Bucket)
{
}

/*virtual*/ QIcon CBucketTool::GetToolIcon() const
{
    QIcon icon("Icons/Bucket.png");
    icon.addFile("Icons/Bucket_Disabled.png", QSize(), QIcon::Mode::Disabled);
    return icon;
}

/*virtual*/ QString CBucketTool::GetToolName() const
{
    return "Paint Bucket";
}

/*virtual*/ QString CBucketTool::GetTooltip() const
{
    return "Fill areas with a color";
}

/*virtual*/ void CBucketTool::ProcessMouseLPressEvent(QMouseEvent* pEvent)
{

}
