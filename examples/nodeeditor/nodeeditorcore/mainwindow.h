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

namespace NodeEditor {

class SampleModel;
class ModelEditorWidget;

//! A main window. Contain two sample models and tabs with two model editors.

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();
    virtual ~MainWindow() override;

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    void write_settings();
    void init_application();

    std::unique_ptr<SampleModel> m_model;
    ModelEditorWidget* m_editorWidget{nullptr};
};

} // namespace NodeEditor

#endif //  MAINWINDOW_H
