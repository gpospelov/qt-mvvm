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

class GraphModel;
class QTabWidget;

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

    QTabWidget* m_tabWidget;
    std::unique_ptr<GraphModel> m_graph_model;
};

#endif //  MAINWINDOW_H
