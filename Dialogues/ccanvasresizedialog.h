#ifndef CCANVASRESIZEDIALOG_H
#define CCANVASRESIZEDIALOG_H

#include <QDialog>
#include "../Enums.h"

namespace Ui {
class CCanvasResizeDialog;
}

class CCanvasResizeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CCanvasResizeDialog(QWidget* pParent, QSize origSize);
    ~CCanvasResizeDialog();

    QSize GetNewSize() const;
    EnumAnchors GetAnchor() const;

private:
    void Init();
    void AddLayout();
    void AddConnections();
    void FillCombobox();

private slots:
    void ChangedWidth(int width);
    void ChangedHeight(int height);
    void ChangedToPixelMode(bool checked);
    void ChangedToPercentMode(bool checked);
    void ChangedOptionAR(Qt::CheckState state);

private:
    Ui::CCanvasResizeDialog *ui;

    class QRadioButton* m_pRadioPixel;
    class QRadioButton* m_pRadioPercent;
    class QSpinBox* m_pSpinWidth;
    class QSpinBox* m_pSpinHeight;
    class QCheckBox* m_pChkAspRatio;
    class QComboBox* m_pComboAnchor;

    QSize m_origSize;
    double m_aspectRatio = 1.0;
};

#endif // CCANVASRESIZEDIALOG_H
