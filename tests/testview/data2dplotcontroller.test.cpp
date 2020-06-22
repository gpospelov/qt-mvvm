// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "customplot_test_utils.h"
#include "google_test.h"
#include "qcustomplot.h"
#include <QSignalSpy>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/plotting/data2dplotcontroller.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/data2ditem.h>
#include <stdexcept>

using namespace ModelView;

//! Testing Data1DPlotController.

class Data2DPlotControllerTest : public ::testing::Test
{
public:
    ~Data2DPlotControllerTest();
};

Data2DPlotControllerTest::~Data2DPlotControllerTest() = default;

//! Initial state.

TEST_F(Data2DPlotControllerTest, initialState)
{
    // Constructor accept valid QCPColorMap
    EXPECT_THROW(Data2DPlotController(nullptr), std::runtime_error);

    auto custom_plot = std::make_unique<QCustomPlot>();
    auto color_map = new QCPColorMap(custom_plot->xAxis, custom_plot->yAxis);
    color_map->data()->clear(); // to remove default values defined in QCPColorMap

    Data2DPlotController controller(color_map);
    EXPECT_EQ(controller.currentItem(), nullptr);

    EXPECT_EQ(color_map->data()->keySize(), 0);
    EXPECT_EQ(color_map->data()->valueSize(), 0);
}

//! Testing controller when Data2DItem is not initialized properly.

TEST_F(Data2DPlotControllerTest, dataItemInInitialState)
{
    // creating custom plot and empty graph on it
    auto custom_plot = std::make_unique<QCustomPlot>();
    auto color_map = new QCPColorMap(custom_plot->xAxis, custom_plot->yAxis);

    // creating data item with single point
    SessionModel model;
    auto data_item = model.insertItem<Data2DItem>();

    // creating controller and point it to Data2DItem
    Data2DPlotController controller(color_map);
    EXPECT_NO_THROW(controller.setItem(data_item));

    // Since data item doesn't contain axes defined, should be no points on colormap.
    EXPECT_EQ(color_map->data()->keySize(), 0);
    EXPECT_EQ(color_map->data()->valueSize(), 0);
}

//! Testing controller when Data2DItem got it's axes after controller was set.

TEST_F(Data2DPlotControllerTest, setAxesAfter)
{
    // creating custom plot and empty graph on it
    auto custom_plot = std::make_unique<QCustomPlot>();
    auto color_map = new QCPColorMap(custom_plot->xAxis, custom_plot->yAxis);

    // creating data item with single point
    SessionModel model;
    auto data_item = model.insertItem<Data2DItem>();

    // creating controller and point it to Data2DItem
    Data2DPlotController controller(color_map);
    EXPECT_NO_THROW(controller.setItem(data_item));

    // setting axes after
    const int nx = 3, ny = 2;
    data_item->setAxes(FixedBinAxisItem::create(nx, 0.0, 3.0),
                       FixedBinAxisItem::create(ny, 0.0, 2.0));

    // color map should get shape of axes
    EXPECT_EQ(color_map->data()->keySize(), nx);
    EXPECT_EQ(color_map->data()->valueSize(), ny);
    EXPECT_EQ(color_map->data()->cell(0, 0), 0.0);
    EXPECT_EQ(color_map->data()->cell(nx - 1, ny - 1), 0.0);
}

//! Testing data points.

TEST_F(Data2DPlotControllerTest, dataPoints)
{
    // creating custom plot and empty graph on it
    auto custom_plot = std::make_unique<QCustomPlot>();
    auto color_map = new QCPColorMap(custom_plot->xAxis, custom_plot->yAxis);

    // creating data item with single point
    SessionModel model;
    auto data_item = model.insertItem<Data2DItem>();
    const int nx = 3, ny = 2;
    data_item->setAxes(FixedBinAxisItem::create(nx, 0.0, 3.0),
                       FixedBinAxisItem::create(ny, 0.0, 2.0));

    // creating controller and point it to Data2DItem
    Data2DPlotController controller(color_map);
    controller.setItem(data_item);

    EXPECT_EQ(color_map->data()->keySize(), nx);
    EXPECT_EQ(color_map->data()->valueSize(), ny);
    EXPECT_EQ(color_map->data()->cell(0, 0), 0.0);
    EXPECT_EQ(color_map->data()->cell(nx - 1, ny - 1), 0.0);

    // setting data points
    std::vector<double> expected = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    data_item->setContent(expected);
    EXPECT_EQ(color_map->data()->cell(0, 0), 1.0);
    EXPECT_EQ(color_map->data()->cell(nx - 1, ny - 1), 6.0);

    // Setting item to nullptr. Current convention is that QCPColorMap loses its data.
    controller.setItem(nullptr);
    EXPECT_EQ(color_map->data()->keySize(), 0);
    EXPECT_EQ(color_map->data()->valueSize(), 0);
}

//! Testing two colormap scenario.

TEST_F(Data2DPlotControllerTest, twoDataItems)
{
    // creating custom plot and empty graph on it
    auto custom_plot = std::make_unique<QCustomPlot>();
    auto color_map = new QCPColorMap(custom_plot->xAxis, custom_plot->yAxis);

    // creating data item with single point
    SessionModel model;
    auto data_item1 = model.insertItem<Data2DItem>();
    const int nx1 = 3, ny1 = 2;
    std::vector<double> expected1 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    data_item1->setAxes(FixedBinAxisItem::create(nx1, 0.0, 3.0),
                        FixedBinAxisItem::create(ny1, 0.0, 2.0));
    data_item1->setContent(expected1);
    auto data_item2 = model.insertItem<Data2DItem>();
    const int nx2 = 2, ny2 = 1;
    std::vector<double> expected2 = {10.0, 20.0};
    data_item2->setAxes(FixedBinAxisItem::create(nx2, 0.0, 3.0),
                        FixedBinAxisItem::create(ny2, 0.0, 2.0));
    data_item2->setContent(expected2);

    // creating controller and point it to first Data2DItem
    Data2DPlotController controller(color_map);
    controller.setItem(data_item1);

    EXPECT_EQ(color_map->data()->keySize(), nx1);
    EXPECT_EQ(color_map->data()->valueSize(), ny1);
    EXPECT_EQ(color_map->data()->cell(0, 0), 1.0);
    EXPECT_EQ(color_map->data()->cell(nx1 - 1, ny1 - 1), 6.0);

    // pointing controller to the second Data2DItem
    controller.setItem(data_item2);

    EXPECT_EQ(color_map->data()->keySize(), nx2);
    EXPECT_EQ(color_map->data()->valueSize(), ny2);
    EXPECT_EQ(color_map->data()->cell(0, 0), 10.0);
    EXPECT_EQ(color_map->data()->cell(nx2 - 1, ny2 - 1), 20.0);
}

//! Testing data range.

TEST_F(Data2DPlotControllerTest, dataRange)
{
    // creating custom plot and empty graph on it
    auto custom_plot = std::make_unique<QCustomPlot>();
    auto color_map = new QCPColorMap(custom_plot->xAxis, custom_plot->yAxis);

    // creating data item with single point
    SessionModel model;
    auto data_item = model.insertItem<Data2DItem>();
    const int nx = 3, ny = 2;
    data_item->setAxes(FixedBinAxisItem::create(nx, 0.0, 3.0),
                       FixedBinAxisItem::create(ny, 0.0, 2.0));
    std::vector<double> expected = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    data_item->setContent(expected);

    // creating controller and point it to Data2DItem
    Data2DPlotController controller(color_map);
    controller.setItem(data_item);

    QSignalSpy spy(color_map, &QCPColorMap::dataRangeChanged);

    auto range = color_map->dataRange();
    EXPECT_EQ(spy.count(), 0);
    EXPECT_EQ(range.lower, 1.0);
    EXPECT_EQ(range.upper, 6.0);
}
