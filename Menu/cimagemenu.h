#ifndef CIMAGEMENU_H
#define CIMAGEMENU_H

#include "cmenubase.h"

class CImageMenu : public CMenuBase
{
public:
    explicit CImageMenu(const QString& title, QWidget* parent);

protected:
    void AddActions();
    void AddConnections();

    template<typename func>
    void ConnectAction(EnumActions e, func&& slot);

private slots:
    void Resize();
    void ResizeCanvas();
    void CropImage();
    void Rotate90C();
    void Rotate90CC();
    void Rotate180();
    void MirrorHor();
    void MirrorVer();

private:
    class CImageManager* m_pImageManager;
};

#endif // CIMAGEMENU_H
