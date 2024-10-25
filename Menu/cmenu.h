#ifndef CMENU_H
#define CMENU_H

#include <qmenu.h>

class CMenu
{
public:
    CMenu(class MainWindow* pParent);

protected:
    void AddFileMenu();
    void AddEditMenu();
    void AddViewMenu();
    void AddImageMenu();
    void AddAdjustmentMenu();
    void AddHelpMenu();

private:
    class MainWindow* m_pParent;

    QMenu* m_pFileMenu;
    QMenu* m_pEditMenu;
    QMenu* m_pViewMenu;
    QMenu* m_pImageMenu;
    QMenu* m_pAdjustmentMenu;
    QMenu* m_pHelpMenu;
};

#endif // CMENU_H
