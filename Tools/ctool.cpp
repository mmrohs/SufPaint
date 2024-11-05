#include "ctool.h"
#include "../Management/cimagemanager.h"


CTool::CTool(EnumTools eTool)
    : m_eTool(eTool)
{
}

/*virtual*/ CTool::~CTool()
{
}

EnumTools CTool::GetToolEnum() const
{
    return m_eTool;
}

/*virtual*/ void CTool::ProcessMouseReleaseEvent(QMouseEvent* pEvent, CImageView* pView)
{
    // add implementation in derived class if necessary
}

/*virtual*/ void CTool::ProcessMouseMoveEvent(QMouseEvent* pEvent, CImageView* pView)
{
    // add implementation in derived class if necessary
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
