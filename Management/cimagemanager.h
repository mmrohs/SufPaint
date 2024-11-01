#ifndef CIMAGEMANAGER_H
#define CIMAGEMANAGER_H

#include <qgraphicsscene.h>
#include <QGraphicsPixmapItem>


// management class for the currently opened image
// (based on the singleton design pattern)
class CImageManager
{
protected:
    explicit CImageManager();

public:
    static CImageManager* GetImageManager();

    // image & image informations
    QImage* GetImage();
    QSize GetImageSize();
    bool HasImage();

    // view & view informations
    void SetImageView(class CImageView* pImageView);
    qreal GetScale();

    // image save/load/... actions
    void NewImage();
    void OpenImage();
    void CloseImage();
    void SaveImage();
    void SaveAsImage();

    // clipboard actions
    void CopyImage();
    void PasteImage();
    void CutImage();

    // zoom actions
    void ZoomIn();
    void ZoomOut();
    void ResetZoom();

    // image size actions
    void Resize();
    void ResizeCanvas();
    void Rotate90C();
    void Rotate90CC();
    void Rotate180();
    void MirrorHor();
    void MirrorVer();

    // color actions
    void InvertColors();
    void Grayscale();
    void Sepia();

private:
    void TrySaveImage(QString strFilePath);
    void ResetImage();
    void UpdateImageView();

private:
    static CImageManager* m_pSingletonInstance;
    class CImageView* m_pImageView;
    QString m_strFilePath;
    QImage* m_pImage;
};

#endif // CIMAGEMANAGER_H
