#include "cimageprocessor.h"
#include <QGuiApplication>
#include <QPainter>
#include <QColorTransform>
#include <QClipboard>
#include <QMimeData>


CImageProcessor::CImageProcessor()
{
}

void CImageProcessor::CopyImage(QImage* pImage)
{
    QClipboard* pClipboard = QGuiApplication::clipboard();
    if (pClipboard != NULL && pImage != NULL)
    {
        pClipboard->setImage(*pImage);
    }
}

void CImageProcessor::CopyImage(QImage* pImage, QRect rect)
{
    QClipboard* pClipboard = QGuiApplication::clipboard();
    if (pClipboard != NULL && pImage != NULL)
    {
        QImage tmpImage = pImage->copy(rect);
        pClipboard->setImage(tmpImage);
    }
}

void CImageProcessor::PasteImage(QImage* pImage)
{
    QClipboard* pClipboard = QGuiApplication::clipboard();
    if (pClipboard != NULL)
    {
        const QMimeData* pMimeData = pClipboard->mimeData();
        if (pMimeData != NULL && pMimeData->hasImage())
        {
            if (pImage == NULL)
            {
                pImage = new QImage();
            }
            *pImage = pClipboard->image();
        }
        else
        {
            qWarning() << "CImageProcessor::PasteImage(): No image in clipboard";
        }
    }
}

void CImageProcessor::CutImage(QImage* pImage, QRect rect)
{
    // copy selected area to clipboard
    QImage tempImage = pImage->copy(rect);
    CopyImage(&tempImage);

    // remove selected area from the original image
    RemoveArea(pImage, rect);
}

 void CImageProcessor::ResizeImage(QImage* pImage, QSize newSize)
{
    *pImage = pImage->scaled(newSize);
}

 void CImageProcessor::ResizeCanvas(QImage* pImage, QSize newSize, EnumAnchors anchor)
{
    // create new image
    QImage newImage(newSize, pImage->format());
    newImage.fill(Qt::white);

    // determine the top-left corner in the new image
    QSize oldSize(pImage->width(), pImage->height());
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

 void CImageProcessor::CropImage(QImage* pImage, QRect rect)
{
    // create new image
    /*QSize newSize(rect.width(), rect.height());
    QImage newImage(newSize, pImage->format());
    newImage.fill(Qt::white);

    // paint old image into new image
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0,0), *pImage, rect);*/

    // old image becomes new image
    QImage newImage = pImage->copy(rect);
    *pImage = newImage;
}

 void CImageProcessor::Rotate90C(QImage* pImage)
{
    QTransform matrix;
    matrix.rotate(90);
    *pImage = pImage->transformed(matrix);
}

 void CImageProcessor::Rotate90CC(QImage* pImage)
{
    QTransform matrix;
    matrix.rotate(270);
    *pImage = pImage->transformed(matrix);
}

 void CImageProcessor::Rotate180(QImage* pImage)
{
    pImage->mirror(true, true);
}

 void CImageProcessor::MirrorHor(QImage* pImage)
{
    pImage->mirror(true, false);
}

 void CImageProcessor::MirrorVer(QImage* pImage)
{
    pImage->mirror(false, true);
}

 void CImageProcessor::InvertColors(QImage* pImage)
{
    int r, g, b;
    for (int y = 0; y < pImage->height(); ++y)
    {
        QRgb* line = reinterpret_cast<QRgb*>(pImage->scanLine(y));
        for (int x = 0; x < pImage->width(); ++x)
        {
            QRgb& rgb = line[x];
            r = 255 - qRed(rgb);
            g = 255 - qGreen(rgb);
            b = 255 - qBlue(rgb);
            rgb = qRgba(r, g, b, qAlpha(rgb));
        }
    }
}

 void CImageProcessor::Grayscale(QImage* pImage)
{
    int c;
    for (int y = 0; y < pImage->height(); ++y)
    {
        QRgb* line = reinterpret_cast<QRgb*>(pImage->scanLine(y));
        for (int x = 0; x < pImage->width(); ++x)
        {
            QRgb& rgb = line[x];
            c = 0.299 * qRed(rgb) + 0.587 * qGreen(rgb) + 0.114 * qBlue(rgb);
            rgb = qRgba(c, c, c, qAlpha(rgb));
        }
    }
}

 void CImageProcessor::Sepia(QImage* pImage)
{
    int c;
    for (int y = 0; y < pImage->height(); ++y)
    {
        QRgb* line = reinterpret_cast<QRgb*>(pImage->scanLine(y));
        for (int x = 0; x < pImage->width(); ++x)
        {
            QRgb& rgb = line[x];
            c = 0.299 * qRed(rgb) + 0.587 * qGreen(rgb) + 0.114 * qBlue(rgb);
            rgb = qRgba(c, 0.8 * c, 0.65 * c, qAlpha(rgb));
        }
    }
}

void CImageProcessor::RemoveArea(QImage* pImage, QRect rect)
{
    static const QRgb transpColor = qRgba(255,255,255,0);
    for (int y = 0; y < pImage->height(); ++y)
    {
        QRgb* line = reinterpret_cast<QRgb*>(pImage->scanLine(y));
        for (int x = 0; x < pImage->width(); ++x)
        {
            if (rect.contains(x, y))
            {
                line[x] = transpColor;
            }
        }
    }
}
