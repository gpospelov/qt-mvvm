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

namespace ModelView {
class AllItemsTreeView;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();

private:
    QGraphicsScene* scene;
    QGraphicsView* view;
    QTimer* timer;
    std::unique_ptr<MouseModel> mouse_model;
    ModelView::AllItemsTreeView* itemsTreeView;
};

#endif //  MAINWINDOW_H
