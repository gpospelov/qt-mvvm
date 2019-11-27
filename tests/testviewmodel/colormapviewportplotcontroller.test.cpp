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
#include <mvvm/model/sessionmodel.h>
#include <mvvm/plotting/colormapviewportplotcontroller.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/colormapitem.h>
#include <mvvm/standarditems/colormapviewportitem.h>
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/data2ditem.h>
#include <qcustomplot.h>

using namespace ModelView;

//! Testing ColorMapViewportPlotController.

class ColorMapViewportPlotControllerTest : public ::testing::Test
{
public:
    ~ColorMapViewportPlotControllerTest();
};

ColorMapViewportPlotControllerTest::~ColorMapViewportPlotControllerTest() = default;

//! Initial state.

TEST_F(ColorMapViewportPlotControllerTest, initialState)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    ColorMapViewportPlotController controller(custom_plot.get());
    EXPECT_EQ(controller.currentItem(), nullptr);
    EXPECT_TRUE(TestUtils::GetPlottable<QCPColorMap>(custom_plot.get()) != nullptr);

    const double customplot_default_lower(0.0), customplot_default_upper(5.0);
    EXPECT_DOUBLE_EQ(custom_plot->xAxis->range().lower, customplot_default_lower);
    EXPECT_DOUBLE_EQ(custom_plot->xAxis->range().upper, customplot_default_upper);
    EXPECT_DOUBLE_EQ(custom_plot->yAxis->range().lower, customplot_default_lower);
    EXPECT_DOUBLE_EQ(custom_plot->yAxis->range().upper, customplot_default_upper);
}

//! Check ::setItem() method when no colormaps exist.

TEST_F(ColorMapViewportPlotControllerTest, setEmptyViewport)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    ColorMapViewportPlotController controller(custom_plot.get());

    SessionModel model;
    auto viewport_item = model.insertItem<ColorMapViewportItem>();

    controller.setItem(viewport_item);

    auto color_map = TestUtils::GetPlottable<QCPColorMap>(custom_plot.get());
    EXPECT_TRUE(color_map != nullptr);

    const double default_lower(0.0), default_upper(1.0);
    EXPECT_DOUBLE_EQ(custom_plot->xAxis->range().lower, default_lower);
    EXPECT_DOUBLE_EQ(custom_plot->xAxis->range().upper, default_upper);
    EXPECT_DOUBLE_EQ(custom_plot->yAxis->range().lower, default_lower);
    EXPECT_DOUBLE_EQ(custom_plot->yAxis->range().upper, default_upper);

    const int qcpmap_internal_default(10);
    EXPECT_EQ(color_map->data()->keySize(), qcpmap_internal_default);
    EXPECT_EQ(color_map->data()->valueSize(), qcpmap_internal_default);
}

//! Check ::setItem() method when data 2d is fully set up.

TEST_F(ColorMapViewportPlotControllerTest, setItem)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    ColorMapViewportPlotController controller(custom_plot.get());

    SessionModel model;
    auto data_item = model.insertItem<Data2DItem>();
    const int nx = 3, ny = 2;
    data_item->setAxes(FixedBinAxisItem::create(nx, 0.0, 3.0),
                       FixedBinAxisItem::create(ny, 0.0, 2.0));
    std::vector<double> expected = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    data_item->setContent(expected);

    // creating colormap item
    auto viewport_item = model.insertItem<ColorMapViewportItem>();
    auto colormap_item = model.insertItem<ColorMapItem>(viewport_item);
    colormap_item->setDataItem(data_item);

    // setting up the controller
    controller.setItem(viewport_item);

    auto color_map = TestUtils::GetPlottable<QCPColorMap>(custom_plot.get());
    EXPECT_EQ(color_map->data()->keySize(), nx);
    EXPECT_EQ(color_map->data()->valueSize(), ny);
    EXPECT_EQ(color_map->data()->cell(0, 0), 1.0);
    EXPECT_EQ(color_map->data()->cell(nx - 1, ny - 1), 6.0);
}

//! Consequitive setup.

TEST_F(ColorMapViewportPlotControllerTest, setupConsequitive)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    ColorMapViewportPlotController controller(custom_plot.get());

    SessionModel model;
    auto viewport_item = model.insertItem<ColorMapViewportItem>();

    controller.setItem(viewport_item);

    auto color_map = TestUtils::GetPlottable<QCPColorMap>(custom_plot.get());
    EXPECT_TRUE(color_map != nullptr);

    // setting up data
    auto data_item = model.insertItem<Data2DItem>();
    const int nx = 3, ny = 2;
    data_item->setAxes(FixedBinAxisItem::create(nx, 0.0, 3.0),
                       FixedBinAxisItem::create(ny, 0.0, 2.0));
    std::vector<double> expected = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    data_item->setContent(expected);

    // creating colormap item
    auto colormap_item = model.insertItem<ColorMapItem>(viewport_item);
    colormap_item->setDataItem(data_item);

    // checking that QCPColorMap has good shape
    EXPECT_EQ(color_map->data()->keySize(), nx);
    EXPECT_EQ(color_map->data()->valueSize(), ny);
    EXPECT_EQ(color_map->data()->cell(0, 0), 1.0);
    EXPECT_EQ(color_map->data()->cell(nx - 1, ny - 1), 6.0);
}
