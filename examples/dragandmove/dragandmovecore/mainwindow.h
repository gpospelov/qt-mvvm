// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DRAGANDMOVECORE_MAINWINDOW_H
#define DRAGANDMOVECORE_MAINWINDOW_H

#include <QMainWindow>
#include <memory>

namespace DragAndMove {

class SampleModel;

//! A main window. Contain two sample models and tabs with two model editors.

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event);

private:
    void writeSettings();
    void initApplication();

    std::unique_ptr<SampleModel> m_model;
};

} // namespace DragAndMove

#endif // DRAGANDMOVECORE_MAINWINDOW_H
