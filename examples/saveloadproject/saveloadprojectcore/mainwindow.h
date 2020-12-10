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

class ActionManager;
class SampleModel;
class ProjectHandler;
class RecentProjectWidget;

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
    void init_components();
    void init_connections();
    void write_settings();

    std::unique_ptr<SampleModel> m_sampleModel;
    ActionManager* m_actionManager{nullptr};
    RecentProjectWidget* m_recentProjectWidget{nullptr};
    ProjectHandler* m_projectHandler{nullptr};
};

#endif //  MAINWINDOW_H
