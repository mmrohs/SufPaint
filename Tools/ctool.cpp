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

QImage* CTool::GetImage() const
{
    CImageManager* pImageManager = CImageManager::GetImageManager();
    if (pImageManager != NULL)
    {
        return pImageManager->GetImage();
    }
    return NULL;
}
