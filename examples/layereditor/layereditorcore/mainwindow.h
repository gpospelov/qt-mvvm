// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef LAYEREDITORCORE_MAINWINDOW_H
#define LAYEREDITORCORE_MAINWINDOW_H

#include <QMainWindow>
#include <memory>

class ApplicationModels;

//! Application main window.

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event);

private:
    void initApplication();
    void writeSettings();
    void createMenus();

    std::unique_ptr<ApplicationModels> m_models;
};

#endif // LAYEREDITORCORE_MAINWINDOW_H
