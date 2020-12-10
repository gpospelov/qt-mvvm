// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

class ApplicationModels;
class QTabWidget;

//! Application main window.

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event);

private:
    void init_application();
    void write_settings();
    void create_menus();

    QTabWidget* m_tabWidget;
    std::unique_ptr<ApplicationModels> m_models;
};

#endif //  MAINWINDOW_H
