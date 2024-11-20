#ifndef CCONNECTOR_H
#define CCONNECTOR_H

#include <QObject>


/* friend class of MainWindow for the connections between widgets etc.
*/
class CConnector : QObject
{
public:
    explicit CConnector(class MainWindow* pMainWindow);

    void ConnectAll();

private:
    void Init();

private:
    // widgets
    class MainWindow*  m_pMainWindow;
    class CImageView*  m_pImageView;
    class CToolWidget* m_pToolWidget;
    class CStatusBar*  m_pStatusBar;

    // managers
    class CImageManager*  m_pImageManager;
    class CActionManager* m_pActionManager;
    class CToolManager*   m_pToolManager;
    class CSelectionManager* m_pSelectionManager;
};

#endif // CCONNECTOR_H
