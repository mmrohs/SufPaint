#ifndef CIMAGEVIEWMANAGER_H
#define CIMAGEVIEWMANAGER_H

#include <qtypes.h>
#include <QPoint>


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
    qreal GetScale() const;
    qreal GetZoom() const;

    // view actions
    void ZoomIn();
    void ZoomOut();
    void ResetZoom();

    // coordinate transformations between image and widget systems
    QPoint GetImagePos(QPoint widgetPos) const;
    QPoint GetWidgetPos(QPoint imagePos) const;

    // Check if the given position is inside the image rect
    // if not then it gets moved into the image
    QPoint CheckPositionInImage(QPoint widgetPos) const;

private:
    static CImageViewManager* m_pSingletonInstance;
    class CImageView* m_pImageView;
};

#endif // CIMAGEVIEWMANAGER_H
