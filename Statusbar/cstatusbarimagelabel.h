#ifndef CSTATUSBARIMAGELABEL_H
#define CSTATUSBARIMAGELABEL_H

#include <QLabel>

class CStatusBarImageLabel : public QLabel
{
public:
    explicit CStatusBarImageLabel(QWidget* pParent);

    void Update();

private:
    void UpdateText();

private:
    QSize m_imageSize;
};

#endif // CSTATUSBARIMAGELABEL_H
