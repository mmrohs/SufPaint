#include "CImageViewManager.h"
#include "../Widgets/cimageview.h"
#include "../Misc/cimageviewtransform.h"


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

qreal CImageViewManager::GetScale() const
{
    if (m_pImageView != NULL)
    {
        return m_pImageView->GetScale();
    }
    return 1.0;
}

qreal CImageViewManager::GetZoom() const
{
    if (m_pImageView != NULL)
    {
        return m_pImageView->GetZoom();
    }
    return 100.0;
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

QPoint CImageViewManager::GetImagePos(QPoint widgetPos, bool bCheckPosition) const
{
    QPoint imgPos;
    const CImageViewTransform* pViewTransform = m_pImageView->GetTransformation();
    if (pViewTransform != NULL)
    {
        imgPos = pViewTransform->TransformWidgetToImage(widgetPos);
        if (bCheckPosition)
        {
            imgPos = pViewTransform->CheckPositionInImage(imgPos);
        }
    }
    return imgPos;
}

QPoint CImageViewManager::GetWidgetPos(QPoint imagePos) const
{
    QPoint wdgPos;
    const CImageViewTransform* pViewTransform = m_pImageView->GetTransformation();
    if (pViewTransform != NULL)
    {
        wdgPos = pViewTransform->TransformImageToWidget(imagePos);
    }
    return wdgPos;
}
