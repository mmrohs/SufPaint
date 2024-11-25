#ifndef CIMAGEMANAGER_H
#define CIMAGEMANAGER_H

#include <QObject>
#include <QImage>


// management class for the currently opened image
// (based on the singleton design pattern)
class CImageManager : public QObject
{
    Q_OBJECT
protected:
    explicit CImageManager();

public:
    static CImageManager* GetImageManager();

    // image & image informations
    QImage* GetImage();
    QSize GetImageSize() const;
    QRect GetImageRect() const;
    bool HasImage() const;

    // set the parent window for dialogues
    void SetParentWindow(QWidget* pParent);

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

    // image size actions
    void Resize();
    void ResizeCanvas();
    void CropImage();
    void Rotate90C();
    void Rotate90CC();
    void Rotate180();
    void MirrorHor();
    void MirrorVer();

    // color actions
    void InvertColors();
    void Grayscale();
    void Sepia();

Q_SIGNALS:
    // signal for pixel changes (e.g. color invert)
    void ImagePixelsUpdate();
    // signal for property changes (e.g. resize)
    void ImagePropertiesUpdate();

public slots:
    // force send the signals above
    void SendImagePixelsUpdate();
    void SendImagePropertiesUpdate();

private:
    class CSelection* GetSelection() const;
    void TrySaveImage(QString strFilePath);
    void ResetImage();

private:
    static CImageManager* m_pSingletonInstance;
    class CImageProcessor* m_pImageProcessor;

    QWidget* m_pParent;
    QImage* m_pImage;
    QString m_strFilePath;
};

#endif // CIMAGEMANAGER_H
