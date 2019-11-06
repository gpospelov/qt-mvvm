// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //


#include <mvvm/standarditems/axisitems.h>
#include "customplot_test_utils.h"
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/plotting/data1dplotcontroller.h>
#include "google_test.h"
#include "qcustomplot.h"
#include <mvvm/model/sessionmodel.h>
#include <algorithm>

using namespace ModelView;

//! Testing Data1DPlotController.

class TestData1DPlotController : public ::testing::Test
{
public:
    ~TestData1DPlotController();
};

TestData1DPlotController::~TestData1DPlotController() = default;

//! Initial state.

TEST_F(TestData1DPlotController, initialState)
{
    // Constructor accept valid QCPGraph
    EXPECT_THROW(Data1DPlotController(nullptr), std::runtime_error);

    auto custom_plot = std::make_unique<QCustomPlot>();
    auto graph = custom_plot->addGraph();

    Data1DPlotController controller(graph);
    EXPECT_EQ(controller.currentItem(), nullptr);

    // no points have been added to graph
    EXPECT_EQ(std::vector<double>(), TestUtils::binCenters(graph));
    EXPECT_EQ(std::vector<double>(), TestUtils::binValues(graph));
}

//! Testing controller when Data1DItem is not initialized properly.

TEST_F(TestData1DPlotController, dataItemInInitialState)
{
    // creating custom plot and empty graph on it
    auto custom_plot = std::make_unique<QCustomPlot>();
    auto graph = custom_plot->addGraph();

    // creating data item with single point
    SessionModel model;
    auto data_item = model.insertItem<Data1DItem>();

    // creating controller and point it to Data1DItem
    Data1DPlotController controller(graph);
    controller.setItem(data_item);

    EXPECT_EQ(std::vector<double>(), TestUtils::binCenters(graph));
    EXPECT_EQ(std::vector<double>(), TestUtils::binValues(graph));
}

//! Testing controller when Data1DItem get it's axis after controller setup.

TEST_F(TestData1DPlotController, axisAfter)
{
    // creating custom plot and empty graph on it
    auto custom_plot = std::make_unique<QCustomPlot>();
    auto graph = custom_plot->addGraph();

    // creating data item with single point
    SessionModel model;
    auto data_item = model.insertItem<Data1DItem>();

    // creating controller and point it to Data1DItem
    Data1DPlotController controller(graph);
    controller.setItem(data_item);

    // setting correct axis
    data_item->setAxis(FixedBinAxisItem::create(1, 1.0, 2.0));
    EXPECT_EQ(data_item->binCenters(), TestUtils::binCenters(graph));
    EXPECT_EQ(data_item->binValues(), TestUtils::binValues(graph));
}

//! Testing graph points update.

TEST_F(TestData1DPlotController, dataPoints)
{
    // creating custom plot and empty graph on it
    auto custom_plot = std::make_unique<QCustomPlot>();
    auto graph = custom_plot->addGraph();

    // creating data item with single point
    SessionModel model;
    auto data_item = model.insertItem<Data1DItem>();
    data_item->setAxis(FixedBinAxisItem::create(1, 1.0, 2.0));

    // creating controller and point it to Data1DItem
    Data1DPlotController controller(graph);
    controller.setItem(data_item);

    // checking that QCPGraph now has data points as in Data1DItem
    EXPECT_EQ(data_item->binCenters(), TestUtils::binCenters(graph));
    EXPECT_EQ(data_item->binValues(), TestUtils::binValues(graph));

    // Setting item to nullptr. Current convention is that graph stays intact, but points disappear.
    controller.setItem(nullptr);
    EXPECT_EQ(std::vector<double>(), TestUtils::binCenters(graph));
    EXPECT_EQ(std::vector<double>(), TestUtils::binValues(graph));
}

//! Testing two graph scenario.

TEST_F(TestData1DPlotController, twoDataItems)
{
    // creating custom plot and empty graph on it
    auto custom_plot = std::make_unique<QCustomPlot>();
    auto graph = custom_plot->addGraph();

    // creating two data items
    SessionModel model;
    auto data_item1 = model.insertItem<Data1DItem>();
    data_item1->setAxis(FixedBinAxisItem::create(1, 1.0, 2.0));
    auto data_item2 = model.insertItem<Data1DItem>();
    data_item2->setAxis(FixedBinAxisItem::create(2, 0.0, 2.0));

    // creating controller and point it to first item
    Data1DPlotController controller(graph);
    controller.setItem(data_item1);

    // checking that QCPGraph now has data points as in first data item
    EXPECT_EQ(data_item1->binCenters(), TestUtils::binCenters(graph));
    EXPECT_EQ(data_item1->binValues(), TestUtils::binValues(graph));

    // pointing controller to the second item
    controller.setItem(data_item2);
    EXPECT_EQ(data_item2->binCenters(), TestUtils::binCenters(graph));
    EXPECT_EQ(data_item2->binValues(), TestUtils::binValues(graph));
}
