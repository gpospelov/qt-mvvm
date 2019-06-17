#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mvvm_global.h"
#include <QMainWindow>
#include <memory>

class ApplicationModels;
class QGraphicsView;

//! Application main window.

class CORE_EXPORT MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event);

private:
    void init_application();
    void init_material_editor();
    void init_sample_editor();
    void write_settings();

    QGraphicsView* m_sample_view;
    QDockWidget* m_material_editor;
    QDockWidget* m_sample_editor;
    std::unique_ptr<ApplicationModels> m_models;
};

#endif // MAINWINDOW_H
