#include "google_test.h"
#include "qcustomplot.h"
#include "graphviewportplotcontroller.h"
#include "graphviewportitem.h"
#include "sessionmodel.h"
#include "data1ditem.h"
#include "graphitem.h"

using namespace ModelView;

//! Testing AxisPlotControllers.

class TestGraphViewportPlotController : public ::testing::Test
{
public:
    ~TestGraphViewportPlotController();
};

TestGraphViewportPlotController::~TestGraphViewportPlotController() = default;

//! Initial state.

TEST_F(TestGraphViewportPlotController, initialState)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    GraphViewportPlotController controller(custom_plot.get());
    EXPECT_EQ(custom_plot->graphCount(), 0);
}

//! Check ::setItem() method when no graphs exist.

TEST_F(TestGraphViewportPlotController, setItem)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    GraphViewportPlotController controller(custom_plot.get());

    // setting up controller with viewport item
    SessionModel model;
    auto item = dynamic_cast<GraphViewportItem*>(model.insertNewItem(Constants::GraphViewportItemType));
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

TEST_F(TestGraphViewportPlotController, addGraphAndSetItem)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    GraphViewportPlotController controller(custom_plot.get());

    // setting up controller with viewport item
    SessionModel model;
    auto viewport_item = dynamic_cast<GraphViewportItem*>(model.insertNewItem(Constants::GraphViewportItemType));

    auto data_item = dynamic_cast<Data1DItem*>(model.insertNewItem(Constants::Data1DItemType));
    const std::vector<double> expected_content = {1.0, 2.0, 3.0};
    const std::vector<double> expected_centers = {0.5, 1.5, 2.5};
    data_item->setFixedBinAxis(3, 0.0, 3.0);
    data_item->setContent(expected_content);

    auto graph_item = dynamic_cast<GraphItem*>(model.insertNewItem(Constants::GraphItemType, viewport_item));
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

TEST_F(TestGraphViewportPlotController, addAndRemoveGraphs)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    GraphViewportPlotController controller(custom_plot.get());

    // setting up controller with viewport item
    SessionModel model;
    auto viewport_item = dynamic_cast<GraphViewportItem*>(model.insertNewItem(Constants::GraphViewportItemType));
    controller.setItem(viewport_item);

    // No graphs yet.
    EXPECT_EQ(custom_plot->graphCount(), 0);

    // Populating with data items
    auto data1 = dynamic_cast<Data1DItem*>(model.insertNewItem(Constants::Data1DItemType));
    const std::vector<double> expected_content1 = {1.0, 2.0, 3.0};
    const std::vector<double> expected_centers = {0.5, 1.5, 2.5};
    data1->setFixedBinAxis(3, 0.0, 3.0);
    data1->setContent(expected_content1);

    auto data2 = dynamic_cast<Data1DItem*>(model.insertNewItem(Constants::Data1DItemType));
    const std::vector<double> expected_content2 = {4.0, 5.0, 6.0};
    data2->setFixedBinAxis(3, 0.0, 3.0);
    data2->setContent(expected_content2);

    // adding graph item to viewport
    auto graph_item1 = dynamic_cast<GraphItem*>(model.insertNewItem(Constants::GraphItemType, viewport_item, "", 0));

    // check that QCustomPlot knows about graph
    EXPECT_EQ(custom_plot->graphCount(), 1);

    graph_item1->setDataItem(data1);

    // check that QCustomPlot knows about graph
    EXPECT_EQ(custom_plot->graphCount(), 1);

    // adding secong graph
    auto graph_item2 = dynamic_cast<GraphItem*>(model.insertNewItem(Constants::GraphItemType, viewport_item, "", 1));
    graph_item2->setDataItem(data2);

    // check that QCustomPlot knows about two graph
    EXPECT_EQ(custom_plot->graphCount(), 2);

    // checking that viewport min, max adjusted to both graphs
    // FIXME for the moment there is now automatic update of ymin, ymax on children change.
    // One have to call update_viewport manually. Should we provide automatic min, max calculation?
    viewport_item->update_viewport();
    EXPECT_DOUBLE_EQ(custom_plot->xAxis->range().lower, expected_centers[0]);
    EXPECT_DOUBLE_EQ(custom_plot->xAxis->range().upper, expected_centers[2]);
    EXPECT_DOUBLE_EQ(custom_plot->yAxis->range().lower, expected_content1[0]);
    EXPECT_DOUBLE_EQ(custom_plot->yAxis->range().upper, expected_content2[2]);

    // removing one GraphItem
    model.removeItem(viewport_item, GraphViewportItem::T_GRAPHS, 1);

    // only single graph should remain on QCustomPlot
    EXPECT_EQ(custom_plot->graphCount(), 1);
}


//! Checks consequitive graph adding/removal

TEST_F(TestGraphViewportPlotController, addMoreGraphs)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    GraphViewportPlotController controller(custom_plot.get());

    // setting up controller with viewport item
    SessionModel model;
    auto viewport_item = dynamic_cast<GraphViewportItem*>(model.insertNewItem(Constants::GraphViewportItemType));
    controller.setItem(viewport_item);

    // No graphs yet.
    EXPECT_EQ(custom_plot->graphCount(), 0);

    // adding graph item to viewport
    // FIXME remove row specification after ItemMapper reporting correct row
    auto graph_item1 = dynamic_cast<GraphItem*>(model.insertNewItem(Constants::GraphItemType, viewport_item, "", 0));
    EXPECT_EQ(custom_plot->graphCount(), 1);

    // FIXME PANIC TODO will crash if uncomment
//    auto graph_item2 = dynamic_cast<GraphItem*>(model.insertNewItem(Constants::GraphItemType, viewport_item, "", 1));
//    EXPECT_EQ(custom_plot->graphCount(), 2);

//    auto graph_item3 = dynamic_cast<GraphItem*>(model.insertNewItem(Constants::GraphItemType, viewport_item, "", 0));
//    EXPECT_EQ(custom_plot->graphCount(), 3);
}



