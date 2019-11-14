// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "qcustomplot.h"
#include <mvvm/model/sessionmodel.h>
#include <mvvm/plotting/graphviewportplotcontroller.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/standarditems/graphviewportitem.h>

using namespace ModelView;

//! Testing GraphViewportPlotController.

class GraphViewportPlotControllerTest : public ::testing::Test
{
public:
    ~GraphViewportPlotControllerTest();
};

GraphViewportPlotControllerTest::~GraphViewportPlotControllerTest() = default;

//! Initial state.

TEST_F(GraphViewportPlotControllerTest, initialState)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    GraphViewportPlotController controller(custom_plot.get());
    EXPECT_EQ(custom_plot->graphCount(), 0);
}

//! Check ::setItem() method when no graphs exist.

TEST_F(GraphViewportPlotControllerTest, setItem)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    GraphViewportPlotController controller(custom_plot.get());

    // setting up controller with viewport item
    SessionModel model;
    auto item = model.insertItem<GraphViewportItem>();
    controller.setItem(item);

    // no graphs in empty GraphViewportItem
    EXPECT_EQ(custom_plot->graphCount(), 0);

    // axis should be [0, 1] as in defaule ViewportAxisItem
    EXPECT_DOUBLE_EQ(custom_plot->xAxis->range().lower, 0.0);
    EXPECT_DOUBLE_EQ(custom_plot->xAxis->range().upper, 1.0);
    EXPECT_DOUBLE_EQ(custom_plot->yAxis->range().lower, 0.0);
    EXPECT_DOUBLE_EQ(custom_plot->yAxis->range().upper, 1.0);
}

//! Check ::setItem() method when ViewPortItem contains graphs.

TEST_F(GraphViewportPlotControllerTest, addGraphAndSetItem)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    GraphViewportPlotController controller(custom_plot.get());

    // setting up controller with viewport item
    SessionModel model;
    auto viewport_item = model.insertItem<GraphViewportItem>();

    auto data_item = model.insertItem<Data1DItem>();
    const std::vector<double> expected_content = {1.0, 2.0, 3.0};
    const std::vector<double> expected_centers = {0.5, 1.5, 2.5};
    data_item->setAxis(FixedBinAxisItem::create(3, 0.0, 3.0));
    data_item->setContent(expected_content);

    auto graph_item = model.insertItem<GraphItem>(viewport_item);
    graph_item->setDataItem(data_item);
    controller.setItem(viewport_item);

    // single graph on custom plot.
    EXPECT_EQ(custom_plot->graphCount(), 1);

    // QCustomPlot axis should correspond to
    EXPECT_DOUBLE_EQ(custom_plot->xAxis->range().lower, expected_centers[0]);
    EXPECT_DOUBLE_EQ(custom_plot->xAxis->range().upper, expected_centers[2]);
    EXPECT_DOUBLE_EQ(custom_plot->yAxis->range().lower, expected_content[0]);
    EXPECT_DOUBLE_EQ(custom_plot->yAxis->range().upper, expected_content[2]);
}

//! Checks consequitive graph adding/removal

TEST_F(GraphViewportPlotControllerTest, addAndRemoveGraphs)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    GraphViewportPlotController controller(custom_plot.get());

    // setting up controller with viewport item
    SessionModel model;
    auto viewport_item = model.insertItem<GraphViewportItem>();
    controller.setItem(viewport_item);

    // No graphs yet.
    EXPECT_EQ(custom_plot->graphCount(), 0);

    // Populating with data items
    auto data1 = model.insertItem<Data1DItem>();
    const std::vector<double> expected_content1 = {1.0, 2.0, 3.0};
    const std::vector<double> expected_centers = {0.5, 1.5, 2.5};
    data1->setAxis(FixedBinAxisItem::create(3, 0.0, 3.0));
    data1->setContent(expected_content1);

    auto data2 = model.insertItem<Data1DItem>();
    const std::vector<double> expected_content2 = {4.0, 5.0, 6.0};
    data2->setAxis(FixedBinAxisItem::create(3, 0.0, 3.0));
    data2->setContent(expected_content2);

    // adding graph item to viewport
    auto graph_item1 = model.insertItem<GraphItem>(viewport_item, {"", 0});

    // check that QCustomPlot knows about graph
    EXPECT_EQ(custom_plot->graphCount(), 1);

    graph_item1->setDataItem(data1);

    // check that QCustomPlot knows about graph
    EXPECT_EQ(custom_plot->graphCount(), 1);

    // adding secong graph
    auto graph_item2 = model.insertItem<GraphItem>(viewport_item, {"", 1});
    graph_item2->setDataItem(data2);

    // check that QCustomPlot knows about two graph
    EXPECT_EQ(custom_plot->graphCount(), 2);

    // Checking that viewport min, max adjusted to both graphs when manually call update_viewport()
    viewport_item->update_viewport();
    EXPECT_DOUBLE_EQ(custom_plot->xAxis->range().lower, expected_centers[0]);
    EXPECT_DOUBLE_EQ(custom_plot->xAxis->range().upper, expected_centers[2]);
    EXPECT_DOUBLE_EQ(custom_plot->yAxis->range().lower, expected_content1[0]);
    EXPECT_DOUBLE_EQ(custom_plot->yAxis->range().upper, expected_content2[2]);

    // removing one GraphItem
    model.removeItem(viewport_item, ViewportItem::T_ITEMS, 1);

    // only single graph should remain on QCustomPlot3
    EXPECT_EQ(custom_plot->graphCount(), 1);
}

//! Checks consequitive graph adding/removal

TEST_F(GraphViewportPlotControllerTest, addMoreGraphs)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    GraphViewportPlotController controller(custom_plot.get());

    // setting up controller with viewport item
    SessionModel model;
    auto viewport_item = model.insertItem<GraphViewportItem>();
    controller.setItem(viewport_item);

    // No graphs yet.
    EXPECT_EQ(custom_plot->graphCount(), 0);

    // adding graph item to viewport
    model.insertItem<GraphItem>(viewport_item);
    EXPECT_EQ(custom_plot->graphCount(), 1);

    model.insertItem<GraphItem>(viewport_item);
    EXPECT_EQ(custom_plot->graphCount(), 2);

    model.insertItem<GraphItem>(viewport_item);
    EXPECT_EQ(custom_plot->graphCount(), 3);
}
