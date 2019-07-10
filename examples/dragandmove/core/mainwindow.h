// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

class QTabWidget;
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
    void init_models();

    QTabWidget* m_tabWidget;
    std::unique_ptr<SampleModel> m_model;
};

#endif //  MAINWINDOW_H
