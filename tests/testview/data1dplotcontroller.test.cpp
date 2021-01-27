// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/plotting/data1dplotcontroller.h"

#include "customplot_test_utils.h"
#include "google_test.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/standarditems/axisitems.h"
#include "mvvm/standarditems/data1ditem.h"
#include <qcustomplot.h>
#include <stdexcept>

using namespace ModelView;

//! Testing Data1DPlotController.

class Data1DPlotControllerTest : public ::testing::Test {
};

//! Initial state.

TEST_F(Data1DPlotControllerTest, initialState)
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

TEST_F(Data1DPlotControllerTest, dataItemInInitialState)
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
    EXPECT_EQ(std::vector<double>(), TestUtils::binErrors(graph));
}

//! Testing controller when Data1DItem get it's axis after controller setup.

TEST_F(Data1DPlotControllerTest, axisAfter)
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
    data_item->setAxis<FixedBinAxisItem>(1, 1.0, 2.0);
    EXPECT_EQ(data_item->binCenters(), TestUtils::binCenters(graph));
    EXPECT_EQ(data_item->binValues(), TestUtils::binValues(graph));
    EXPECT_EQ(std::vector<double>(), TestUtils::binErrors(graph));
}

//! Testing graph points update.

TEST_F(Data1DPlotControllerTest, dataPoints)
{
    // creating custom plot and empty graph on it
    auto custom_plot = std::make_unique<QCustomPlot>();
    auto graph = custom_plot->addGraph();

    // creating data item with single point
    SessionModel model;
    auto data_item = model.insertItem<Data1DItem>();
    data_item->setAxis<FixedBinAxisItem>(1, 1.0, 2.0);

    // creating controller and point it to Data1DItem
    Data1DPlotController controller(graph);
    controller.setItem(data_item);

    // checking that QCPGraph now has data points as in Data1DItem
    EXPECT_EQ(data_item->binCenters(), TestUtils::binCenters(graph));
    EXPECT_EQ(data_item->binValues(), TestUtils::binValues(graph));
    EXPECT_EQ(data_item->binErrors(), TestUtils::binErrors(graph));

    // Setting item to nullptr. Current convention is that graph stays intact, but points disappear.
    controller.setItem(nullptr);
    EXPECT_EQ(std::vector<double>(), TestUtils::binCenters(graph));
    EXPECT_EQ(std::vector<double>(), TestUtils::binValues(graph));
    EXPECT_EQ(std::vector<double>(), TestUtils::binErrors(graph));
}

//! Testing graph errors update.

TEST_F(Data1DPlotControllerTest, errorBars)
{
    // creating custom plot and empty graph on it
    auto custom_plot = std::make_unique<QCustomPlot>();
    auto graph = custom_plot->addGraph();

    // creating data item with single point
    SessionModel model;
    auto data_item = model.insertItem<Data1DItem>();
    data_item->setAxis<FixedBinAxisItem>(2, 1.0, 2.0);

    // creating controller and point it to Data1DItem
    Data1DPlotController controller(graph);
    controller.setItem(data_item);

    std::vector<double> expected_errors = {0.1, 0.2};
    data_item->setErrors(expected_errors);
    EXPECT_EQ(TestUtils::binErrors(graph), expected_errors);

    // setting new errors
    expected_errors = {0.3, 0.4};
    data_item->setErrors(expected_errors);
    EXPECT_EQ(TestUtils::binErrors(graph), expected_errors);
}

//! Testing two graph scenario.

TEST_F(Data1DPlotControllerTest, twoDataItems)
{
    // creating custom plot and empty graph on it
    auto custom_plot = std::make_unique<QCustomPlot>();
    auto graph = custom_plot->addGraph();

    // creating two data items
    SessionModel model;
    auto data_item1 = model.insertItem<Data1DItem>();
    data_item1->setAxis<FixedBinAxisItem>(1, 1.0, 2.0);
    auto data_item2 = model.insertItem<Data1DItem>();
    data_item2->setAxis<FixedBinAxisItem>(2, 0.0, 2.0);

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
