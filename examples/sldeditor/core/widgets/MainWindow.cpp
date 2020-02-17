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
#include "ViewItemsModel.h"
#include "ViewWidget.h"

#include "HandleItem.h"
#include "HandleView.h"

#include "SegmentItem.h"
#include "SegmentView.h"

#include "RoughnessItem.h"
#include "RoughnessView.h"

#include <QAction>
#include <QCoreApplication>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QSettings>
#include <QTreeView>

#include <mvvm/model/modelutils.h>
#include <mvvm/widgets/standardtreeviews.h>

#include <iostream>

namespace
{
const QString main_window_group = "MainWindow";
const QString size_key = "size";
const QString pos_key = "pos";
} // namespace

MainWindow::MainWindow()
    : view_widget(new ViewWidget), models(std::make_unique<ApplicationModels>())
{
    auto widget = new QWidget();
    auto layout = new QHBoxLayout(widget);
    auto tree = new ModelView::AllItemsTreeView(models->viewItemsModel());

    layout->addWidget(view_widget);
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

    std::vector<std::vector<double>> values{
        {50., 50.}, {80., 40.}, {50., 30.}, {90., 50.}, {50., 0.}};

    std::vector<SegmentView*> top_segments;
    std::vector<std::vector<HandleView*>> handles;

    double edge = 0;
    for (const auto& data : values) {

        // initialise segments
        SegmentItem* segment_item = models->viewItemsModel()->addSegment();
        SegmentView* segment = new SegmentView(segment_item);
        view_widget->getScene()->addItem(segment);
        top_segments.push_back(segment);

        // set parameters
        segment_item->setProperty(SegmentItem::P_X_POS, data[0] / 2 + edge);
        segment_item->setProperty(SegmentItem::P_Y_POS, data[1]);
        segment_item->setProperty(SegmentItem::P_WIDTH, data[0]);
        edge += data[0];

        // initialise handles
        HandleItem* handle_item_left = models->viewItemsModel()->addHandle();
        HandleItem* handle_item_right = models->viewItemsModel()->addHandle();
        HandleView* handle_left = new HandleView(handle_item_left);
        HandleView* handle_right = new HandleView(handle_item_right);
        view_widget->getScene()->addItem(handle_left);
        view_widget->getScene()->addItem(handle_right);
        handles.push_back(std::vector<HandleView*>{handle_left, handle_right});

        // set the handles
        segment->addHandles(handle_left, handle_right);
    }

    std::vector<SegmentView*> side_segments;
    edge = 0;
    for (int i = 1; i < top_segments.size(); ++i) {
        edge += values[i - 1][0];

        // initialise segments
        SegmentItem* segment_item = models->viewItemsModel()->addSegment();
        SegmentView* segment = new SegmentView(segment_item);
        view_widget->getScene()->addItem(segment);
        side_segments.push_back(segment);

        // set parameters
        segment_item->setProperty(SegmentItem::P_HORIZONTAL, false);
        segment_item->setProperty(SegmentItem::P_X_POS, edge);
        segment_item->setProperty(
            SegmentItem::P_Y_POS,
            (top_segments[i]->segmentItem()->property(SegmentItem::P_Y_POS).toDouble()
             - top_segments[i - 1]->segmentItem()->property(SegmentItem::P_Y_POS).toDouble())
                    / 2.
                + top_segments[i - 1]->segmentItem()->property(SegmentItem::P_Y_POS).toDouble());
        segment_item->setProperty(
            SegmentItem::P_HEIGHT,
            (top_segments[i]->segmentItem()->property(SegmentItem::P_Y_POS).toDouble()
             - top_segments[i - 1]->segmentItem()->property(SegmentItem::P_Y_POS).toDouble()));
        segment_item->setProperty(
            SegmentItem::P_WIDTH,
            top_segments[i - 1]->segmentItem()->property(SegmentItem::P_HEIGHT).toDouble());

        // set the handles
        segment->addHandles(handles[i - 1][1], handles[i][0]);
    }

    handles[0][0]->setFlag(QGraphicsItem::ItemIsMovable);
    handles[(handles.size()) - 1][1]->setFlag(QGraphicsItem::ItemIsMovable);

    auto roughness_item = models->viewItemsModel()->addRoughness();
    auto roughness_view = new RoughnessView(roughness_item);
    roughness_view->setSegments(side_segments[0], top_segments[1], side_segments[1]);

    // view_widget->scene()->addItem(roughness_view);

    view_widget->getScene()->setContext();
    // view_widget->getScene()->addItem(axes_view);
}
