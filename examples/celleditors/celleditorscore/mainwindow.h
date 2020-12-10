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

namespace CellEditors
{

class SampleModel;

//! A main window. Contain two sample models and tabs with two model editors.

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    virtual ~MainWindow() override;

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    void write_settings();
    void init_application();
    void init_models();

    QTabWidget* m_tabWidget{nullptr};
    std::unique_ptr<SampleModel> m_model;
};

} // namespace CellEditors

#endif //  MAINWINDOW_H
