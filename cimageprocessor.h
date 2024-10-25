#ifndef CIMAGEPROCESSOR_H
#define CIMAGEPROCESSOR_H

#include <QImage>
#include "Enums.h"


class CImageProcessor
{
protected:
    CImageProcessor();

public:
    // size and orientation
    static void ResizeImage(QImage* pImage, QSize newSize);
    static void ResizeCanvas(QImage* pImage, QSize newSize, EnumAnchors anchor);
    static void Rotate90C(QImage* pImage);
    static void Rotate90CC(QImage* pImage);
    static void Rotate180(QImage* pImage);
    static void MirrorHor(QImage* pImage);
    static void MirrorVer(QImage* pImage);

    // colors
    static void InvertColors(QImage* pImage);
    static void Grayscale(QImage* pImage);
    static void Sepia(QImage* pImage);
};

#endif // CIMAGEPROCESSOR_H
