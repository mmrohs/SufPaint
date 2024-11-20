#ifndef CNEWIMAGEDIALOG_H
#define CNEWIMAGEDIALOG_H

#include <QDialog>

namespace Ui {
class CNewImageDialog;
}

class CNewImageDialog : public QDialog
{
    Q_OBJECT
    enum EnumTemplate { INVALID = -1, CUSTOM = 0, S640X480, S800X600, S1024X768, S1600X1200 };
public:
    explicit CNewImageDialog(QWidget* pParent);
    ~CNewImageDialog();

    // returns the image size
    QSize GetSize() const;

protected:
    virtual void paintEvent(QPaintEvent* pEvent) override;

private:
    void Init();
    void AddLayout();
    void AddConnections();
    void FillCombobox();

    int GetTemplateWidth(EnumTemplate) const;
    int GetTemplateHeight(EnumTemplate) const;
    QString GetTemplateText(EnumTemplate) const;
    QRect CalcPreviewRect() const;

private slots:
    void SetImageSize();
    void SetCustomSize();
    void UpdatePreview();

private:
    Ui::CNewImageDialog* ui;

    class QGroupBox* m_pGBoxPreview;
    class QComboBox* m_pComboTemplates;
    class QSpinBox* m_pSpinWidth;
    class QSpinBox* m_pSpinHeight;
};

#endif // CNEWIMAGEDIALOG_H
