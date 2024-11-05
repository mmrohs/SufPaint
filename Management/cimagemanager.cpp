#include "cimagemanager.h"
#include <QGuiApplication>
#include <QException>
#include <QFileDialog>
#include <QClipboard>
#include <QMimeData>
#include <QPainter>
//#include "cactionmanager.h"
//#include "cimageviewmanager.h"
#include "../Dialogues/cimageresizedialog.h"
#include "../Dialogues/ccanvasresizedialog.h"
#include "../Dialogues/cnewimagedialog.h"
#include "../cimageprocessor.h"
//#include <qgraphicsscene.h>
//#include <QGraphicsPixmapItem>


/*static*/ CImageManager* CImageManager::m_pSingletonInstance = NULL;

CImageManager::CImageManager()
    : m_pParent(NULL), m_pImage(NULL)
{
}

/*static*/ CImageManager* CImageManager::GetImageManager()
{
    if (m_pSingletonInstance == NULL)
    {
        m_pSingletonInstance = new CImageManager();
    }
    return m_pSingletonInstance;
}

void CImageManager::SetParentWindow(QWidget* pParent)
{
    m_pParent = pParent;
}

QImage* CImageManager::GetImage()
{
    return m_pImage;
}

QSize CImageManager::GetImageSize() const
{
    QSize size;
    if (m_pImage != NULL)
    {
        size = m_pImage->size();
    }
    return size;
}

QRect CImageManager::GetImageRect() const
{
    QRect rect;
    if (m_pImage != NULL)
    {
        rect = m_pImage->rect();
    }
    return rect;
}

bool CImageManager::HasImage() const
{
    return m_pImage != NULL;
}

void CImageManager::NewImage()
{
    CNewImageDialog* pDialog = new CNewImageDialog(m_pParent);
    pDialog->exec();
    if (pDialog->result() == QDialog::Accepted)
    {
        ResetImage();

        m_pImage = new QImage(pDialog->GetWidth(), pDialog->GetHeight(), QImage::Format_ARGB32);
        m_pImage->fill(QColor(255,255,255));

        emit ImageUpdate();
    }
}

void CImageManager::OpenImage()
{
    m_strFilePath = QFileDialog::getOpenFileName(m_pParent,
                        QObject::tr("Open Image"), QObject::tr("/home"), QObject::tr("Image types (*.bmp *.jpg *.png)"));
    if (!m_strFilePath.isEmpty())
    {
        ResetImage();
        m_pImage = new QImage(m_strFilePath);
        emit ImageUpdate();
    }
}

void CImageManager::CloseImage()
{
    ResetImage();
    m_strFilePath = QString();
}

void CImageManager::SaveImage()
{
    if (!m_strFilePath.isEmpty())
    {
        TrySaveImage(m_strFilePath);
    }
    else
    {
        qWarning() << "CImageManager::SaveImage(): m_strFilePath.isEmpty() == true";
    }
}

void CImageManager::SaveAsImage()
{
    if (m_pImage != NULL)
    {
        QString strFilePath = QFileDialog::getSaveFileName(m_pParent,
                                QObject::tr("Save Image"), QObject::tr("/home"), QObject::tr("Image types (*.bmp *.jpg *.png)"));
        if (!strFilePath.isEmpty())
        {
            TrySaveImage(strFilePath);
        }
        else
        {
            qWarning() << "CImageManager::SaveAsImage(): strFilePath.isEmpty()";
        }
    }
}

void CImageManager::CopyImage()
{
    if (m_pImage != NULL)
    {
        QClipboard* pClipboard = QGuiApplication::clipboard();
        if (pClipboard != NULL)
        {
            pClipboard->setImage(*m_pImage);
        }
    }
}

void CImageManager::PasteImage()
{
    QClipboard* pClipboard = QGuiApplication::clipboard();
    if (pClipboard != NULL)
    {
        const QMimeData* pMimeData = pClipboard->mimeData();
        if (pMimeData != NULL && pMimeData->hasImage())
        {
            ResetImage();
            m_pImage = new QImage(pClipboard->image());
            emit ImageUpdate();
        }
        else
        {
            qWarning() << "CImageManager::PasteImage(): No image in clipboard";
        }
    }
}

void CImageManager::CutImage()
{
    // to do
}

void CImageManager::Resize()
{
    if (m_pImage != NULL)
    {
        QSize origSize(m_pImage->width(), m_pImage->height());
        CImageResizeDialog* pDialog = new CImageResizeDialog(m_pParent, origSize);
        pDialog->exec();
        if (pDialog->result() == QDialog::Accepted)
        {
            QSize newSize = pDialog->GetNewSize();
            if (newSize != origSize)
            {
                CImageProcessor::ResizeImage(m_pImage, newSize);
                emit ImageUpdate();
            }
        }
        delete pDialog;
    }
}

void CImageManager::ResizeCanvas()
{
    if (m_pImage != NULL)
    {
        QSize origSize(m_pImage->width(), m_pImage->height());
        CCanvasResizeDialog* pDialog = new CCanvasResizeDialog(m_pParent, origSize);
        pDialog->exec();
        if (pDialog->result() == QDialog::Accepted)
        {
            QSize newSize = pDialog->GetNewSize();
            if (newSize != origSize)
            {
                EnumAnchors anchor = pDialog->GetAnchor();
                CImageProcessor::ResizeCanvas(m_pImage, newSize, anchor);
                emit ImageUpdate();
            }
        }
        delete pDialog;
    }
}

void CImageManager::Rotate90C()
{
    if (m_pImage != NULL)
    {
        CImageProcessor::Rotate90C(m_pImage);
        emit ImageUpdate();
    }
}

void CImageManager::Rotate90CC()
{
    if (m_pImage != NULL)
    {
        CImageProcessor::Rotate90CC(m_pImage);
        emit ImageUpdate();
    }
}

void CImageManager::Rotate180()
{
    if (m_pImage != NULL)
    {
        CImageProcessor::Rotate180(m_pImage);
        emit ImageUpdate();
    }
}

void CImageManager::MirrorHor()
{
    if (m_pImage != NULL)
    {
        CImageProcessor::MirrorHor(m_pImage);
        emit ImageUpdate();
    }
}

void CImageManager::MirrorVer()
{
    if (m_pImage != NULL)
    {
        CImageProcessor::MirrorVer(m_pImage);
        emit ImageUpdate();
    }
}

void CImageManager::InvertColors()
{
    if (m_pImage != NULL)
    {
        CImageProcessor::InvertColors(m_pImage);
        emit ImageUpdate();
    }
}

void CImageManager::Grayscale()
{
    if (m_pImage != NULL)
    {
        CImageProcessor::Grayscale(m_pImage);
        emit ImageUpdate();
    }
}

void CImageManager::Sepia()
{
    if (m_pImage != NULL)
    {
        CImageProcessor::Sepia(m_pImage);
        emit ImageUpdate();
    }
}

void CImageManager::TrySaveImage(QString strFilePath)
{
    try
    {
        m_pImage->save(strFilePath);
        m_strFilePath = strFilePath;
    }
    catch (QException* e)
    {
        QString strException(e->what());
        qWarning() << "CImageManager::TrySaveImage(): exception " + strException;
    }
    catch (...)
    {
        qWarning() << "CImageManager::TrySaveImage(): unknown exception";
    }
}

void CImageManager::ResetImage()
{
    if (m_pImage != NULL)
    {
        delete m_pImage;
        m_pImage = NULL;
        emit ImageUpdate();
    }
}

/*
void CImageManager::UpdateImageView()
{
    // update the visible image
    CImageViewManager::GetImageViewManager();
    if (m_pParent != NULL)
    {
        m_pParent->SetImage(m_pImage);
    }

    // update the enabled/disabled actions
    CActionManager* pActionManager = CActionManager::GetActionManager();
    if (pActionManager != NULL)
    {
        pActionManager->CheckAllActions();
    }
}
*/
