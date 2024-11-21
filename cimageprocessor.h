#ifndef CIMAGEPROCESSOR_H
#define CIMAGEPROCESSOR_H

#include <QImage>
#include "Enums.h"


class CImageProcessor
{
public:
    CImageProcessor();

    // clipboard
    void CopyImage(QImage* pImage);
    void CopyImage(QImage* pImage, QRect rect);
    void PasteImage(QImage* pImage);
    void CutImage(QImage* pImage, QRect rect);

    // size and orientation
    void ResizeImage(QImage* pImage, QSize newSize);
    void ResizeCanvas(QImage* pImage, QSize newSize, EnumAnchors anchor);
    void CropImage(QImage* pImage, QRect rect);
    void Rotate90C(QImage* pImage);
    void Rotate90CC(QImage* pImage);
    void Rotate180(QImage* pImage);
    void MirrorHor(QImage* pImage);
    void MirrorVer(QImage* pImage);

    // colors
    void InvertColors(QImage* pImage);
    void Grayscale(QImage* pImage);
    void Sepia(QImage* pImage);

    // misc
    void RemoveArea(QImage* pImage, QRect rect);
};

#endif // CIMAGEPROCESSOR_H
