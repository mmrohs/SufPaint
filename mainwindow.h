#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qgraphicsscene.h>
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
    void AddConnections();
    void SetupManagers();

private:
    Ui::MainWindow* m_pUI;

    // Visible Widgets
    class CImageView* m_pImageView;
    class CToolWidget* m_pToolWidget;
    class CColorWidget* m_pColorWidget;
    class CLayerWidget* m_pLayerWidget;

    // Menu, Toolbar and StatusBar
    CMenu* m_pMenu;
    QToolBar* m_pToolBar;
    CStatusBar* m_pStatusBar;
};
#endif // MAINWINDOW_H
