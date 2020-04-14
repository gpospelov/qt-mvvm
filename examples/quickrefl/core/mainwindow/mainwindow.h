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

class ImportWindow;
class ReflDockWindow;
class MainBarWidget;
class ApplicationModels;

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
    void init_tabs();
    void write_settings();

    std::unique_ptr<ApplicationModels> models;
    ImportWindow* import_window{nullptr};
    ReflDockWindow* refl_window{nullptr};
    MainBarWidget* bar_widget{nullptr};
};

#endif //  MAINWINDOW_H
