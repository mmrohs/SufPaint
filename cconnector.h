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
    class MainWindow*   m_pMainWindow;
};

#endif // CCONNECTOR_H
