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
#include <QDebug>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QMenuBar>
#include <QSlider>
#include <QTimer>
#include <QToolBar>
#include <QVBoxLayout>
#include <mvvm/model/modelutils.h>
#include <mvvm/widgets/standardtreeviews.h>

namespace
{
const int msec_update_period = 30;
const int max_slider_value = 100;
} // namespace

MainWindow::MainWindow()
    : scene(new QGraphicsScene)
    , view(new QGraphicsView(scene))
    , timer(new QTimer)
    , slider(new QSlider)
    , mouse_model(std::make_unique<MouseModel>())
    , itemsTreeView(new ModelView::AllItemsTreeView(mouse_model.get()))
{
    create_central_widget();
    init_scene();
    init_toolbar();
    init_menu();

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

    populate_scene();
}

//! Inits toolbar.

void MainWindow::init_toolbar()
{
    auto toolbar = addToolBar("toolbar");

    // creates pause/resume button
    auto pause_resume_action = new QAction("Pause/Resume", this);
    auto on_pause_action = [this]() {
        if (timer->isActive()) {
            timer->stop();
        } else {
            timer->start(msec_update_period);
            slider->setValue(max_slider_value);
        }
    };
    connect(pause_resume_action, &QAction::triggered, on_pause_action);
    toolbar->addAction(pause_resume_action);

    toolbar->addSeparator();

    // creates undo/redo slider
    toolbar->addWidget(new QLabel("   Back in time  "));
    slider->setRange(0, max_slider_value);
    slider->setValue(max_slider_value);
    slider->setOrientation(Qt::Horizontal);
    slider->setMaximumWidth(300);
    toolbar->addWidget(slider);

    auto on_slider_moved = [this](auto value) { mouse_model->setUndoPosition(value); };
    connect(slider, &QSlider::sliderMoved, on_slider_moved);

    auto on_slider_pressed = [this]() { timer->stop(); };
    connect(slider, &QSlider::sliderPressed, on_slider_pressed);
}

//! Initializes file save/load menu.

void MainWindow::init_menu()
{
    auto fileMenu = menuBar()->addMenu("&File");

    // open file
    auto openAction = new QAction("&Open...", this);
    fileMenu->addAction(openAction);
    auto onOpenAction = [&]() {
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty()) {
            mouse_model->readFromFile(fileName);
            populate_scene();
        }
    };
    connect(openAction, &QAction::triggered, onOpenAction);

    // save file
    auto saveAction = new QAction("&Save As...", this);
    fileMenu->addAction(saveAction);

    auto onSaveAction = [&]() {
        QString fileName = QFileDialog::getSaveFileName(this);
        if (!fileName.isEmpty())
            mouse_model->writeToFile(fileName);
    };
    connect(saveAction, &QAction::triggered, onSaveAction);
}

//! Populates scene with content from the model.

void MainWindow::populate_scene()
{
    scene->clear();
    for (auto item : mouse_model->topItems<MouseItem>())
        scene->addItem(new Mouse(item));
}
