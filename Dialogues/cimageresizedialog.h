#ifndef CIMAGERESIZEDIALOG_H
#define CIMAGERESIZEDIALOG_H

#include <QDialog>

namespace Ui {
class CImageResizeDialog;
}

class CImageResizeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CImageResizeDialog(QWidget* pParent, QSize origSize);
    ~CImageResizeDialog();

    QSize GetNewSize() const;

private:
    void Init();
    void AddLayout();
    void AddConnections();

private slots:
    void ChangedWidth(int width);
    void ChangedHeight(int height);
    void ChangedToPixelMode(bool checked);
    void ChangedToPercentMode(bool checked);
    void ChangedOptionAR(Qt::CheckState state);

private:
    Ui::CImageResizeDialog* ui;

    class QRadioButton* m_pRadioPixel;
    class QRadioButton* m_pRadioPercent;
    class QSpinBox* m_pSpinWidth;
    class QSpinBox* m_pSpinHeight;
    class QCheckBox* m_pChkAspRatio;

    QSize m_origSize;
    double m_aspectRatio = 1.0;
};

#endif // CIMAGERESIZEDIALOG_H
