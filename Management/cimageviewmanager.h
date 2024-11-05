#ifndef CIMAGEVIEWMANAGER_H
#define CIMAGEVIEWMANAGER_H

#include <qtypes.h>


// management class for the image view
// (based on the singleton design pattern)
class CImageViewManager
{
protected:
    explicit CImageViewManager();

public:
    static CImageViewManager* GetImageViewManager();

    // needs to be called from MainWindow!
    void SetImageView(class CImageView* pImageView);

    // view information
    qreal GetZoom();

    // view actions
    void ZoomIn();
    void ZoomOut();
    void ResetZoom();

private:
    static CImageViewManager* m_pSingletonInstance;
    class CImageView* m_pImageView;
};

#endif // CIMAGEVIEWMANAGER_H
