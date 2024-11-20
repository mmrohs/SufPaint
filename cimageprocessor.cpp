#include "cimageprocessor.h"
#include <QPainter>
#include <QColorTransform>


CImageProcessor::CImageProcessor()
{}

/*static*/ void CImageProcessor::ResizeImage(QImage* pImage, QSize newSize)
{
    *pImage = pImage->scaled(newSize);
}

/*static*/ void CImageProcessor::ResizeCanvas(QImage* pImage, QSize newSize, EnumAnchors anchor)
{
    QSize oldSize(pImage->width(), pImage->height());

    // create new image
    QImage newImage(newSize, pImage->format());
    newImage.fill(Qt::white);

    // determine the top-left corner in the new image
    QPoint posTopLeft(0, 0);
    if (anchor == EnumAnchors::Center)
    {
        posTopLeft.setX(0.5 * (newSize.width() - oldSize.width()));
        posTopLeft.setY(0.5 * (newSize.height() - oldSize.height()));
    }
    else if (anchor == EnumAnchors::Top)
    {
        posTopLeft.setX(0.5 * (newSize.width() - oldSize.width()));
    }
    else if (anchor == EnumAnchors::TopRight)
    {
        posTopLeft.setX(newSize.width() - oldSize.width());
    }
    else if (anchor == EnumAnchors::Right)
    {
        posTopLeft.setX(newSize.width() - oldSize.width());
        posTopLeft.setY(0.5 * (newSize.height() - oldSize.height()));
    }
    else if (anchor == EnumAnchors::BottomRight)
    {
        posTopLeft.setX(newSize.width() - oldSize.width());
        posTopLeft.setY(newSize.height() - oldSize.height());
    }
    else if (anchor == EnumAnchors::Bottom)
    {
        posTopLeft.setX(0.5 * (newSize.width() - oldSize.width()));
        posTopLeft.setY(newSize.height() - oldSize.height());
    }
    else if (anchor == EnumAnchors::BottomLeft)
    {
        posTopLeft.setY(newSize.height() - oldSize.height());
    }
    else if (anchor == EnumAnchors::Left)
    {
        posTopLeft.setY(0.5 * (newSize.height() - oldSize.height()));
    }

    // paint old image into new image
    QPainter painter(&newImage);
    painter.drawImage(posTopLeft, *pImage);

    // old image becomes new image
    *pImage = newImage;
}

/*static*/ void CImageProcessor::CropImage(QImage* pImage, QRect rect)
{
    // create new image
    QSize newSize(rect.width(), rect.height());
    QImage newImage(newSize, pImage->format());
    newImage.fill(Qt::white);

    // paint old image into new image
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0,0), *pImage, rect);

    // old image becomes new image
    *pImage = newImage;
}

/*static*/ void CImageProcessor::Rotate90C(QImage* pImage)
{
    QTransform matrix;
    matrix.rotate(90);
    *pImage = pImage->transformed(matrix);
}

/*static*/ void CImageProcessor::Rotate90CC(QImage* pImage)
{
    QTransform matrix;
    matrix.rotate(270);
    *pImage = pImage->transformed(matrix);
}

/*static*/ void CImageProcessor::Rotate180(QImage* pImage)
{
    pImage->mirror(true, true);
}

/*static*/ void CImageProcessor::MirrorHor(QImage* pImage)
{
    pImage->mirror(true, false);
}

/*static*/ void CImageProcessor::MirrorVer(QImage* pImage)
{
    pImage->mirror(false, true);
}

/*static*/ void CImageProcessor::InvertColors(QImage* pImage)
{
    for (int i = 0; i < pImage->height(); ++i)
    {
        QRgb* line = reinterpret_cast<QRgb*>(pImage->scanLine(i));
        for (int j = 0; j < pImage->width(); ++j)
        {
            QRgb& rgb = line[j];
            rgb = qRgba(255 - qRed(rgb), 255 - qGreen(rgb), 255 - qBlue(rgb), qAlpha(rgb));
        }
    }
}

/*static*/ void CImageProcessor::Grayscale(QImage* pImage)
{
    int x;
    for (int i = 0; i < pImage->height(); ++i)
    {
        QRgb* line = reinterpret_cast<QRgb*>(pImage->scanLine(i));
        for (int j = 0; j < pImage->width(); ++j)
        {
            QRgb& rgb = line[j];
            x = 0.299 * qRed(rgb) + 0.587 * qGreen(rgb) + 0.114 * qBlue(rgb);
            rgb = qRgba(x, x, x, qAlpha(rgb));
        }
    }
}

/*static*/ void CImageProcessor::Sepia(QImage* pImage)
{
    int x;
    for (int i = 0; i < pImage->height(); ++i)
    {
        QRgb* line = reinterpret_cast<QRgb*>(pImage->scanLine(i));
        for (int j = 0; j < pImage->width(); ++j)
        {
            QRgb& rgb = line[j];
            x = 0.299 * qRed(rgb) + 0.587 * qGreen(rgb) + 0.114 * qBlue(rgb);
            rgb = qRgba(x, 0.8 * x, 0.65 * x, qAlpha(rgb));
        }
    }
}
