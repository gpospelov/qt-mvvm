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
class RecentProjectManager;

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
    void init_widgets();
    void write_settings();

    ActionManager* m_actionManager{nullptr};
    RecentProjectManager* m_recentProjectManager{nullptr};
    std::unique_ptr<SampleModel> m_sample_model;
};

#endif //  MAINWINDOW_H
