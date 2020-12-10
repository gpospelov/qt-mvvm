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

class QTabWidget;

namespace PlotGraphs
{

class GraphModel;

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

    QTabWidget* m_tabWidget{nullptr};
    std::unique_ptr<GraphModel> m_graph_model;
};

} // namespace PlotGraphs

#endif //  MAINWINDOW_H
