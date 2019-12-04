// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mainwindow.h"
#include "mouse.h"
#include "mousemodel.h"
#include <mvvm/model/modelutils.h>
#include <mvvm/widgets/standardtreeviews.h>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTabWidget>
#include <QTimer>
#include <QVBoxLayout>
#include <QAction>
#include <QToolBar>

namespace
{
const QString main_window_group = "MainWindow";
const QString size_key = "size";
const QString pos_key = "pos";
} // namespace

MainWindow::MainWindow()
    : scene(new QGraphicsScene), view(new QGraphicsView(scene)), timer(new QTimer),
      mouse_model(std::make_unique<MouseModel>()),
      itemsTreeView(new ModelView::AllItemsTreeView(mouse_model.get()))
{
    auto central_widget = new QWidget;
    auto layout = new QHBoxLayout;
    layout->addWidget(itemsTreeView, 2);
    layout->addWidget(view, 5);
    central_widget->setLayout(layout);


    auto toolbar = addToolBar("xxx");

    auto pause_action = new QAction;
    auto on_pause_action = [this]() {
        if (timer->isActive())
            timer->stop();
        else
            timer->start(1000 / 33);
    };
    connect(pause_action, &QAction::triggered, on_pause_action);

    toolbar->addAction(pause_action);


    scene->setSceneRect(-300, -300, 600, 600);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    for (auto item : ModelView::Utils::TopItems<MouseItem>(mouse_model.get()))
        scene->addItem(new Mouse(item));

    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QPixmap(":/images/cheese.jpg"));

    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->setDragMode(QGraphicsView::ScrollHandDrag);

    view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Colliding Mice"));

    setCentralWidget(central_widget);
    resize(1200, 900);

    QObject::connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
    timer->start(1000 / 33);
}

MainWindow::~MainWindow() = default;
