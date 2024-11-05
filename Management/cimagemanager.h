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
    void ImageUpdate();

private:
    void TrySaveImage(QString strFilePath);
    void ResetImage();

private:
    static CImageManager* m_pSingletonInstance;
    QWidget* m_pParent;
    QString m_strFilePath;
    QImage* m_pImage;
};

#endif // CIMAGEMANAGER_H
