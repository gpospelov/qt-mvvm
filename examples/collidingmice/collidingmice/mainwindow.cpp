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
#include <QAction>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QToolBar>
#include <QVBoxLayout>
#include <mvvm/model/modelutils.h>
#include <mvvm/widgets/standardtreeviews.h>

namespace
{
const int msec_update_period = 30;
} // namespace

MainWindow::MainWindow()
    : scene(new QGraphicsScene), view(new QGraphicsView(scene)), timer(new QTimer),
      pause_resume_action(new QAction("Pause/Resume")), mouse_model(std::make_unique<MouseModel>()),
      itemsTreeView(new ModelView::AllItemsTreeView(mouse_model.get()))
{
    create_central_widget();
    init_scene();
    init_toolbar();

    QObject::connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
    timer->start(msec_update_period);
}

MainWindow::~MainWindow() = default;

void MainWindow::create_central_widget()
{
    auto central_widget = new QWidget;
    auto layout = new QHBoxLayout;
    layout->addWidget(itemsTreeView, 2);
    layout->addWidget(view, 5);
    central_widget->setLayout(layout);
    setCentralWidget(central_widget);
    resize(1200, 900);
    setWindowTitle("Colliding Mice");
}

void MainWindow::init_scene()
{
    scene->setSceneRect(-300, -300, 600, 600);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QPixmap(":/images/cheese.jpg"));
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->setDragMode(QGraphicsView::ScrollHandDrag);

    for (auto item : ModelView::Utils::TopItems<MouseItem>(mouse_model.get()))
        scene->addItem(new Mouse(item));
}

void MainWindow::init_toolbar()
{
    auto toolbar = addToolBar("toolbar");

    auto on_pause_action = [this]() {
        if (timer->isActive())
            timer->stop();
        else
            timer->start(msec_update_period);
    };
    connect(pause_resume_action, &QAction::triggered, on_pause_action);
    toolbar->addAction(pause_resume_action);
}
