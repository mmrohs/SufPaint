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

void CImageViewManager::MoveView(QPoint distance)
{
    if (m_pImageView != NULL)
    {
        m_pImageView->MoveView(distance);
    }
}

void CImageViewManager::ResetZoom()
{
    if (m_pImageView != NULL)
    {
        m_pImageView->ResetZoom();
    }
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

QPoint CImageViewManager::GetImagePos(QPoint widgetPos) const
{
    QPoint imagePos;
    const CImageViewTransform* pViewTransform = m_pImageView->GetTransformation();
    if (pViewTransform != NULL)
    {
        imagePos = pViewTransform->TransformWidgetToImage(widgetPos);
    }
    return imagePos;
}

QPoint CImageViewManager::GetWidgetPos(QPoint imagePos) const
{
    QPoint widgetPos;
    const CImageViewTransform* pViewTransform = m_pImageView->GetTransformation();
    if (pViewTransform != NULL)
    {
        widgetPos = pViewTransform->TransformImageToWidget(imagePos);
    }
    return widgetPos;
}

QPoint CImageViewManager::CheckPositionInImage(QPoint widgetPos) const
{
    const CImageViewTransform* pViewTransform = m_pImageView->GetTransformation();
    if (pViewTransform != NULL)
    {
        widgetPos = pViewTransform->CheckPositionInImage(widgetPos);
    }
    return widgetPos;
}
