#include "cstatusbarimagelabel.h"
#include "../Management/cimagemanager.h"


CStatusBarImageLabel::CStatusBarImageLabel(QWidget* pParent)
    : QLabel("", pParent)
{
    UpdateText();
}

void CStatusBarImageLabel::Update()
{
    CImageManager* pImageManager = CImageManager::GetImageManager();
    if (pImageManager != NULL)
    {
        m_imageSize = pImageManager->GetImageSize();
        UpdateText();
    }
}

void CStatusBarImageLabel::UpdateText()
{
    int width = m_imageSize.width();
    int height = m_imageSize.height();
    if (width >= 0 && height >= 0)
    {
        setText(QString(" Image size: %1 x %2").arg(width).arg(height));
    }
    else
    {
        setText(QString(" Image size: -"));
    }
}
