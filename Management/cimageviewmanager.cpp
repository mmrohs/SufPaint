#include "CImageViewManager.h"
#include "../Widgets/cimageview.h"


/*static*/ CImageViewManager* CImageViewManager::m_pSingletonInstance = NULL;

CImageViewManager::CImageViewManager()
{
}

/*static*/ CImageViewManager* CImageViewManager::GetImageViewManager()
{
    if (m_pSingletonInstance == NULL)
    {
        m_pSingletonInstance = new CImageViewManager();
    }
    return m_pSingletonInstance;
}

void CImageViewManager::SetImageView(CImageView* pImageView)
{
    assert(pImageView != NULL);
    m_pImageView = pImageView;
}

qreal CImageViewManager::GetZoom()
{
    if (m_pImageView != NULL)
    {
        return m_pImageView->GetZoom();
    }
    return 0.0;
}

void CImageViewManager::ZoomIn()
{
    if (m_pImageView != NULL)
    {
        m_pImageView->ZoomIn();
    }
}

void CImageViewManager::ZoomOut()
{
    if (m_pImageView != NULL)
    {
        m_pImageView->ZoomOut();
    }
}

void CImageViewManager::ResetZoom()
{
    if (m_pImageView != NULL)
    {
        m_pImageView->ResetZoom();
    }
}
