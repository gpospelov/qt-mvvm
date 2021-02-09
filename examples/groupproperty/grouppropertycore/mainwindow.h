// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GROUPPROPERTYCORE_MAINWINDOW_H
#define GROUPPROPERTYCORE_MAINWINDOW_H

#include <QMainWindow>
#include <memory>

namespace GroupProperty {

//! The main window of this application.

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
};

} // namespace PlotGraphs

#endif // GROUPPROPERTYCORE_MAINWINDOW_H
