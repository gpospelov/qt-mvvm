#include "google_test.h"
#include "qcustomplot.h"
#include "graphplotcontroller.h"
#include "graphitem.h"
#include "sessionmodel.h"
#include "data1ditem.h"
#include "customplot_test_utils.h"
#include <QSignalSpy>

using namespace ModelView;

//! Testing GraphPlotController.

class TestGraphPlotController : public ::testing::Test
{
public:
    ~TestGraphPlotController();
};

TestGraphPlotController::~TestGraphPlotController() = default;

//! Initial state.

TEST_F(TestGraphPlotController, initialState)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    GraphPlotController controller(custom_plot.get());
    EXPECT_EQ(custom_plot->graphCount(), 0);
}

//! Setting GraphItem with data and checking that plottable contains correct data.

TEST_F(TestGraphPlotController, setItem)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    GraphPlotController controller(custom_plot.get());

    // setup model and single data item in it
    SessionModel model;
    auto data_item = dynamic_cast<Data1DItem*>(model.insertNewItem(Constants::Data1DItemType));
    data_item->setFixedBinAxis(2, 0.0, 2.0);
    std::vector<double> expected_centers = {0.5, 1.5};
    std::vector<double> expected_values = {42.0, 43.0};
    data_item->setContent(expected_values);

    // setup graph item
    auto graph_item = dynamic_cast<GraphItem*>(model.insertNewItem(Constants::GraphItemType));
    graph_item->setProperty(GraphItem::P_COLOR, QColor(Qt::red));
    graph_item->setDataItem(data_item);

    // initializing controller
    controller.setItem(graph_item);

    // Checking resulting plottables
    EXPECT_EQ(custom_plot->graphCount(), 1);
    auto graph = custom_plot->graph();
    EXPECT_EQ(TestUtils::binCenters(graph), expected_centers);
    EXPECT_EQ(TestUtils::binValues(graph), expected_values);
    EXPECT_EQ(graph->pen().color(), QColor(Qt::red));
}

//!Unlinking from data item

TEST_F(TestGraphPlotController, unlinkFromDataItem)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    GraphPlotController controller(custom_plot.get());

    // setup model and single data item in it
    SessionModel model;
    auto data_item = dynamic_cast<Data1DItem*>(model.insertNewItem(Constants::Data1DItemType));
    data_item->setFixedBinAxis(2, 0.0, 2.0);
    std::vector<double> expected_centers = {0.5, 1.5};
    std::vector<double> expected_values = {42.0, 43.0};
    data_item->setContent(expected_values);

    // setup graph item
    auto graph_item = dynamic_cast<GraphItem*>(model.insertNewItem(Constants::GraphItemType));
    graph_item->setProperty(GraphItem::P_COLOR, QColor(Qt::red));
    graph_item->setDataItem(data_item);

    // initializing controller
    controller.setItem(graph_item);

    // unlinking from data item
    graph_item->setDataItem(nullptr);

    // Checking resulting plottables
    // FIXME Current convention is that graph stays intact, but points disappear. Is it the right thing?
    EXPECT_EQ(custom_plot->graphCount(), 1);
    auto graph = custom_plot->graph();
    EXPECT_EQ(TestUtils::binCenters(graph), std::vector<double>());
    EXPECT_EQ(TestUtils::binValues(graph), std::vector<double>());
    EXPECT_EQ(graph->pen().color(), QColor(Qt::red));

    // unlinking from graph item
    controller.setItem(nullptr);
    EXPECT_EQ(custom_plot->graphCount(), 0);
}

//! Deletion of controller should lead to graph removal.

TEST_F(TestGraphPlotController, controllerDelete)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    auto controller = std::make_unique<GraphPlotController>(custom_plot.get());

    // setup model and single data item in it
    SessionModel model;
    auto data_item = dynamic_cast<Data1DItem*>(model.insertNewItem(Constants::Data1DItemType));

    // setup graph item
    auto graph_item = dynamic_cast<GraphItem*>(model.insertNewItem(Constants::GraphItemType));
    graph_item->setDataItem(data_item);

    // initializing controller
    controller->setItem(graph_item);
    EXPECT_EQ(custom_plot->graphCount(), 1);

    // deleting controller should lead to graph removal
    controller.reset();
    EXPECT_EQ(custom_plot->graphCount(), 0);

    //  inserting item again
    graph_item = dynamic_cast<GraphItem*>(model.insertNewItem(Constants::GraphItemType));
    graph_item->setDataItem(data_item);
}

