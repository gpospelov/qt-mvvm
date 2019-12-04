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

class QGraphicsScene;
class QGraphicsView;
class QTimer;
class MouseModel;
class QAction;

namespace ModelView
{
class AllItemsTreeView;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();

private:
    void create_central_widget();
    void init_scene();
    void init_toolbar();

    QGraphicsScene* scene;
    QGraphicsView* view;
    QTimer* timer;
    QAction* pause_resume_action;
    std::unique_ptr<MouseModel> mouse_model;
    ModelView::AllItemsTreeView* itemsTreeView;
};

#endif //  MAINWINDOW_H
