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
#include <QCoreApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QSettings>
#include <QTabWidget>
#include <QTimer>
#include <math.h>

static const int MouseCount = 7;

namespace
{
const QString main_window_group = "MainWindow";
const QString size_key = "size";
const QString pos_key = "pos";
} // namespace

MainWindow::MainWindow()
    : scene(new QGraphicsScene), view(new QGraphicsView(scene)), timer(new QTimer),
      mouse_model(std::make_unique<MouseModel>())
{
    scene->setSceneRect(-300, -300, 600, 600);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    int i = 0;
    for (auto item : ModelView::Utils::TopItems<MouseItem>(mouse_model.get())) {
        Mouse* mouse = new Mouse(item);
        mouse->setPos(::sin((i * 6.28) / MouseCount) * 200, ::cos((i * 6.28) / MouseCount) * 200);
        scene->addItem(mouse);
        ++i;
    }

    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QPixmap(":/images/cheese.jpg"));

    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->setDragMode(QGraphicsView::ScrollHandDrag);

    view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Colliding Mice"));

    setCentralWidget(view);
    resize(800, 600);

    QObject::connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
    timer->start(1000 / 33);
}

MainWindow::~MainWindow() = default;
