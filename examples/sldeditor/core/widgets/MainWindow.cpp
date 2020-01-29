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
#include "HandleView.h"

#include "SegmentItem.h"
#include "SegmentView.h"

#include <QAction>
#include <QCoreApplication>
#include <QFileDialog>
#include <QMenuBar>
#include <QSettings>
#include <QTreeView>
#include <QHBoxLayout>

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

    std::vector<std::vector<double>> values;
    values.push_back(std::vector<double>{50.,50.});
    values.push_back(std::vector<double>{80.,40.});
    values.push_back(std::vector<double>{50.,30.});
    values.push_back(std::vector<double>{90.,50.});
    values.push_back(std::vector<double>{50.,0.});

    std::vector<SegmentView*> top_segments;
    std::vector<std::vector<HandleView*>> handles;

    double edge = 0;
    for (std::vector<double> data : values){

        //initialise segments
        SegmentItem* segment_item = m_models->viewItemsModel()->addSegment();
        SegmentView* segment = new SegmentView(segment_item);
        m_view_widget->scene()->addItem(segment); 
        top_segments.push_back(segment);

        //set parameters
        segment_item->setProperty(SegmentItem::P_X_POS, data[0]/2+edge);
        segment_item->setProperty(SegmentItem::P_Y_POS, data[1]);
        segment_item->setProperty(SegmentItem::P_WIDTH, data[0]);
        edge += data[0];

        //initialise handles
        HandleItem* handle_item_left = m_models->viewItemsModel()->addHandle();
        HandleItem* handle_item_right = m_models->viewItemsModel()->addHandle();
        HandleView* handle_left = new HandleView(handle_item_left);
        HandleView* handle_right = new HandleView(handle_item_right);
        m_view_widget->scene()->addItem(handle_left);
        m_view_widget->scene()->addItem(handle_right);
        handles.push_back(std::vector<HandleView*>{handle_left, handle_right});

        //set the handles
        segment->addHandles(handle_left, handle_right);

    }

    std::vector<SegmentView*> side_segments;
    edge = 0;
    for (int i = 1; i < top_segments.size(); ++i){
        edge += values[i-1][0];

        //initialise segments
        SegmentItem* segment_item = m_models->viewItemsModel()->addSegment();
        SegmentView* segment = new SegmentView(segment_item);
        m_view_widget->scene()->addItem(segment); 
        side_segments.push_back(segment);

        //set parameters
        segment_item->setProperty(SegmentItem::P_HORIZONTAL, false);
        segment_item->setProperty(SegmentItem::P_X_POS, edge);
        segment_item->setProperty(
            SegmentItem::P_Y_POS, 
            (top_segments[i]->segmentItem()->property(SegmentItem::P_Y_POS).toDouble() 
            - top_segments[i-1]->segmentItem()->property(SegmentItem::P_Y_POS).toDouble())/2.
            + top_segments[i-1]->segmentItem()->property(SegmentItem::P_Y_POS).toDouble());
        segment_item->setProperty(
            SegmentItem::P_HEIGHT, 
            (top_segments[i]->segmentItem()->property(SegmentItem::P_Y_POS).toDouble() 
            - top_segments[i-1]->segmentItem()->property(SegmentItem::P_Y_POS).toDouble()));
        segment_item->setProperty(
            SegmentItem::P_WIDTH, 
            top_segments[i-1]->segmentItem()->property(SegmentItem::P_HEIGHT).toDouble());

        //set the handles
        segment->addHandles(handles[i-1][1], handles[i][0]);
    }

    handles[0][0]->setFlag(QGraphicsItem::ItemIsMovable);
    handles[(handles.size())-1][1]->setFlag(QGraphicsItem::ItemIsMovable);

}
