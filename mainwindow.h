#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qgraphicsscene.h>
#include "cconnector.h"
#include "Menu/cmenu.h"
#include "Statusbar/cstatusbar.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* pParent = nullptr);
    ~MainWindow();

public slots:
    void UpdateActions();

private:
    void AddMenu();
    void AddToolbar();
    void AddStatusBar();
    void AddLayout();
    void SetupManagers();

private:
    Ui::MainWindow* m_pUI;
    CConnector m_connector;

    // visible widgets
    class CImageView* m_pImageView;
    class CToolWidget* m_pToolWidget;
    class CColorWidget* m_pColorWidget;
    class CLayerWidget* m_pLayerWidget;

    // menu, toolbar and statusbar
    CMenu* m_pMenu;
    QToolBar* m_pToolBar;
    CStatusBar* m_pStatusBar;

    friend class CConnector;
};
#endif // MAINWINDOW_H
