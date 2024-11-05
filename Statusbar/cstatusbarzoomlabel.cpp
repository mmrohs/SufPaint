#include "cstatusbarzoomlabel.h"
#include "../Management/cimageviewmanager.h"


CStatusBarZoomLabel::CStatusBarZoomLabel(QWidget* pParent)
    : QLabel("", pParent)
{
    SetZoom(100.0);
}

void CStatusBarZoomLabel::Update()
{
    qreal zoom = CImageViewManager::GetImageViewManager()->GetZoom();
    SetZoom(zoom);
}

void CStatusBarZoomLabel::SetZoom(qreal zoom)
{
    setText(QString("Zoom: %1%").arg(QString::number(zoom, 'd', 1)));
}
