#include "cstatusbarzoomlabel.h"
#include "../Management/cimagemanager.h"


CStatusBarZoomLabel::CStatusBarZoomLabel(QWidget* pParent)
    : QLabel("", pParent)
{
    SetZoom(100.0);
}

void CStatusBarZoomLabel::Update()
{
    CImageManager* pImageManager = CImageManager::GetImageManager();
    if (pImageManager != NULL)
    {
        SetZoom(100.0 * pImageManager->GetScale());
    }
}

void CStatusBarZoomLabel::SetZoom(qreal zoom)
{
    setText(QString("Zoom: %1%").arg(QString::number(zoom, 'd', 1)));
}
