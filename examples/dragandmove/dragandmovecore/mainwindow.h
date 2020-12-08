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

namespace DragAndView
{

class SampleModel;

//! A main window. Contain two sample models and tabs with two model editors.

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event);

private:
    void write_settings();
    void init_application();

    QTabWidget* m_tabWidget;
    std::unique_ptr<SampleModel> m_model;
};

} // namespace DragAndView

#endif //  MAINWINDOW_H
