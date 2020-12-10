// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GRAPHICSPROXY_MAINWINDOW_H
#define GRAPHICSPROXY_MAINWINDOW_H

#include <QMainWindow>
#include <memory>

class SceneModel;
class QTabWidget;

//! The main window of this application.

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
    void init_model();

    std::unique_ptr<SceneModel> m_model;
};

#endif //  GRAPHICSPROXY_MAINWINDOW_H
