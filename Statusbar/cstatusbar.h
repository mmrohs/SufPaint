#ifndef CSTATUSBAR_H
#define CSTATUSBAR_H

#include <qlabel.h>

class CStatusBar : public QObject
{
    Q_OBJECT
public:
    CStatusBar(class MainWindow* pParent);

public slots:
    void ImageUpdate();
    void ToolUpdate();
    void ZoomUpdate();

private:
    void AddStatusBarItems();

private:
    class MainWindow* m_pParent;
    QLabel* m_pSBImageLabel;
    QLabel* m_pSBToolLabel;
    QLabel* m_pSBZoomLabel;
};

#endif // CSTATUSBAR_H
