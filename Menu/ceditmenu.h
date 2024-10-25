#ifndef CEDITMENU_H
#define CEDITMENU_H

#include "cmenubase.h"

class CEditMenu : public CMenuBase
{
public:
    explicit CEditMenu(const QString& title, QWidget* parent);

protected:
    void AddActions();
    void AddConnections();

    template<typename func>
    void ConnectAction(EnumActions e, func&& slot);

private slots:
    void CopyImage();
    void PasteImage();
    void CutImage();

private:
    class CImageManager* m_pImageManager;
};

#endif // CEDITMENU_H
