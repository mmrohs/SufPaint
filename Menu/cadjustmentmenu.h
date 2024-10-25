#ifndef CADJUSTMENTMENU_H
#define CADJUSTMENTMENU_H

#include "cmenubase.h"

class CAdjustmentMenu : public CMenuBase
{
public:
    explicit CAdjustmentMenu(const QString& title, QWidget* parent);

protected:
    void AddActions();
    void AddConnections();

    template<typename func>
    void ConnectAction(EnumActions e, func&& slot);

private slots:
    // color effects:
    void InvertColors();
    void Grayscale();
    void Sepia();

private:
    class CImageManager* m_pImageManager;
};

#endif // CADJUSTMENTMENU_H
