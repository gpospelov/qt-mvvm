// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GRAPHICSPROXY_MAINWINDOW_H
#define GRAPHICSPROXY_MAINWINDOW_H

#include <QMainWindow>
#include <memory>

namespace GraphicsProxy {

class SceneModel;

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

    std::unique_ptr<SceneModel> m_model;
};

} // namespace GraphicsProxy

#endif //  GRAPHICSPROXY_MAINWINDOW_H
