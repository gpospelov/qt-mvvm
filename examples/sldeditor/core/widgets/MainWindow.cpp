// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "MainWindow.h"
#include "AppModels.h"
#include "ViewWidget.h"
#include "ViewItemsModel.h"

#include "HandleItem.h"
#include "Handle.h"
#include "SegmentItem.h"
#include "Segment.h"

#include <QAction>
#include <QCoreApplication>
#include <QFileDialog>
#include <QMenuBar>
#include <QSettings>
#include <QTreeView>
#include <QHBoxLayout>

#include <mvvm/model/modelutils.h>
#include <mvvm/widgets/standardtreeviews.h>

namespace
{
const QString main_window_group = "MainWindow";
const QString size_key = "size";
const QString pos_key = "pos";
} // namespace

MainWindow::MainWindow()
    : m_view_widget(new ViewWidget), 
    m_models(std::make_unique<ApplicationModels>())
{   
    auto widget = new QWidget();
    auto layout = new QHBoxLayout(widget);
    auto tree = new ModelView::AllItemsTreeView(m_models->viewItemsModel());

    layout->addWidget(m_view_widget);
    layout->addWidget(tree);

    setCentralWidget(widget);
    initApplication();
}

MainWindow::~MainWindow() = default;

void MainWindow::closeEvent(QCloseEvent* event)
{
    QMainWindow::closeEvent(event);
}

void MainWindow::initApplication()
{
    QCoreApplication::setApplicationName("qt-mvvm-example");
    QCoreApplication::setApplicationVersion("0.1");
    QCoreApplication::setOrganizationName("qt-mvvm");

    QSettings settings;
    if (settings.childGroups().contains(main_window_group)) {
        settings.beginGroup(main_window_group);
        resize(settings.value(size_key, QSize(400, 400)).toSize());
        move(settings.value(pos_key, QPoint(200, 200)).toPoint());
        settings.endGroup();
    }

    HandleItem* handle_item_left = m_models->viewItemsModel()->addHandle();
    HandleItem* handle_item_right = m_models->viewItemsModel()->addHandle();

    Handle* handle_left = new Handle(handle_item_left);
    Handle* handle_right = new Handle(handle_item_right);

    m_view_widget->scene()->addItem(handle_left);
    m_view_widget->scene()->addItem(handle_right);

    SegmentItem* segment_item = m_models->viewItemsModel()->addSegment();
    Segment* segment = new Segment(segment_item);
    m_view_widget->scene()->addItem(segment); 

    segment->addHandles(handle_left, handle_right);
}
