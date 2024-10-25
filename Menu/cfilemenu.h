#ifndef CFILEMENU_H
#define CFILEMENU_H

#include "cmenubase.h"

class CFileMenu : public CMenuBase
{
public:
    explicit CFileMenu(const QString& title, QWidget* pParent);

protected:
    void AddActions();
    void AddConnections();

    template<typename func>
    void ConnectAction(EnumActions e, func&& slot);

private slots:
    void NewImage();
    void OpenImage();
    void CloseImage();
    void SaveImage();
    void SaveAsImage();
    void Quit();

private:
    class CImageManager* m_pImageManager;
};

#endif // CFILEMENU_H
