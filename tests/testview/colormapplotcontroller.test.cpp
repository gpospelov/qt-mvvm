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
#include <mvvm/model/comboproperty.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/plotting/colormapplotcontroller.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/colormapitem.h>
#include <mvvm/standarditems/data2ditem.h>

using namespace ModelView;

//! Testing ColorMapPlotController.

class ColorMapPlotControllerTest : public ::testing::Test
{
public:
    ~ColorMapPlotControllerTest();
};

ColorMapPlotControllerTest::~ColorMapPlotControllerTest() = default;

//! Initial state.

TEST_F(ColorMapPlotControllerTest, initialState)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    ColorMapPlotController controller(custom_plot.get());
    EXPECT_EQ(controller.currentItem(), nullptr);

    // creation of controller leads to the creation of QCPColorMap
    auto color_map = TestUtils::GetPlottable<QCPColorMap>(custom_plot.get());
    ASSERT_TRUE(color_map != nullptr);
}

//! Setting ColorMapItem with data and checking that QCPColorMap appeared among plottables.

TEST_F(ColorMapPlotControllerTest, setItem)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    ColorMapPlotController controller(custom_plot.get());

    // creating data item
    SessionModel model;
    auto data_item = model.insertItem<Data2DItem>();
    const int nx = 3, ny = 2;
    data_item->setAxes(FixedBinAxisItem::create(nx, 0.0, 3.0),
                       FixedBinAxisItem::create(ny, 0.0, 2.0));
    std::vector<double> expected = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    data_item->setContent(expected);

    // creating colormap item
    auto colormap_item = model.insertItem<ColorMapItem>();
    colormap_item->setDataItem(data_item);

    // initializing controller
    controller.setItem(colormap_item);

    // checking that QCPColorMap has been created
    EXPECT_EQ(custom_plot->plottableCount(), 1);
    auto color_map = TestUtils::GetPlottable<QCPColorMap>(custom_plot.get());
    ASSERT_TRUE(color_map != nullptr);
    EXPECT_EQ(color_map->data()->keySize(), nx);
    EXPECT_EQ(color_map->data()->valueSize(), ny);
    EXPECT_EQ(color_map->data()->cell(0, 0), 1.0);
    EXPECT_EQ(color_map->data()->cell(nx - 1, ny - 1), 6.0);

    // checking interpolation flag
    EXPECT_TRUE(color_map->interpolate());
}

//! Setting data to graph after.

TEST_F(ColorMapPlotControllerTest, setDataAfter)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    ColorMapPlotController controller(custom_plot.get());

    SessionModel model;
    auto colormap_item = model.insertItem<ColorMapItem>();

    controller.setItem(colormap_item);

    // without data QCustomPlot has QCPColorMap without default settings
    EXPECT_EQ(custom_plot->plottableCount(), 1);
    auto color_map = TestUtils::GetPlottable<QCPColorMap>(custom_plot.get());
    ASSERT_TRUE(color_map != nullptr);
    const int qcpmap_internal_default(10);
    EXPECT_EQ(color_map->data()->keySize(), qcpmap_internal_default);
    EXPECT_EQ(color_map->data()->valueSize(), qcpmap_internal_default);

    // setup Data2DItem and assign to ColorMapItem
    auto data_item = model.insertItem<Data2DItem>();
    const int nx = 3, ny = 2;
    data_item->setAxes(FixedBinAxisItem::create(nx, 0.0, 3.0),
                       FixedBinAxisItem::create(ny, 0.0, 2.0));
    std::vector<double> expected = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    data_item->setContent(expected);

    colormap_item->setDataItem(data_item);

    // colormap should get the shape of Data2DItem
    EXPECT_EQ(color_map->data()->keySize(), nx);
    EXPECT_EQ(color_map->data()->valueSize(), ny);
    EXPECT_EQ(color_map->data()->cell(0, 0), 1.0);
    EXPECT_EQ(color_map->data()->cell(nx - 1, ny - 1), 6.0);
}

//! Unlinking from Data2DItem or ColorMapItem.

TEST_F(ColorMapPlotControllerTest, unlinkFromItem)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    ColorMapPlotController controller(custom_plot.get());

    // setup model and single data item in it
    SessionModel model;
    auto data_item = model.insertItem<Data2DItem>();
    const int nx = 3, ny = 2;
    data_item->setAxes(FixedBinAxisItem::create(nx, 0.0, 3.0),
                       FixedBinAxisItem::create(ny, 0.0, 2.0));
    std::vector<double> expected = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    data_item->setContent(expected);

    // creating colormap item
    auto colormap_item = model.insertItem<ColorMapItem>();
    colormap_item->setDataItem(data_item);

    controller.setItem(colormap_item);

    auto color_map = TestUtils::GetPlottable<QCPColorMap>(custom_plot.get());
    EXPECT_EQ(color_map->data()->keySize(), nx);
    EXPECT_EQ(color_map->data()->valueSize(), ny);

    // unlinking from data item
    colormap_item->setDataItem(nullptr);

    EXPECT_EQ(custom_plot->plottableCount(), 1);

    // QCPColorMap should be there, but its shapre should be (0,0)
    EXPECT_EQ(color_map->data()->keySize(), 0);
    EXPECT_EQ(color_map->data()->valueSize(), 0);

    // unlinking from ColorMapItem leave QCPColorMap intact
    controller.setItem(nullptr);
    EXPECT_EQ(custom_plot->plottableCount(), 1);
    EXPECT_EQ(color_map->data()->keySize(), 0);
    EXPECT_EQ(color_map->data()->valueSize(), 0);
}

//! Deletion of controller should lead to graph removal.

TEST_F(ColorMapPlotControllerTest, controllerDelete)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    auto controller = std::make_unique<ColorMapPlotController>(custom_plot.get());

    // setup model and single data item in it
    SessionModel model;
    auto data_item = model.insertItem<Data2DItem>();

    // setup graph item
    auto colormap_item = model.insertItem<ColorMapItem>();
    colormap_item->setDataItem(data_item);

    // initializing controller
    controller->setItem(colormap_item);
    EXPECT_EQ(custom_plot->plottableCount(), 1);

    // deleting controller should lead to QCPColorMap removal
    controller.reset();
    EXPECT_EQ(custom_plot->plottableCount(), 0);
}

//! Deletion of controller should lead to graph removal.

TEST_F(ColorMapPlotControllerTest, setGradient)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    auto controller = std::make_unique<ColorMapPlotController>(custom_plot.get());

    // setup model and single data item in it
    SessionModel model;
    auto data_item = model.insertItem<Data2DItem>();

    // creating colormap item
    auto colormap_item = model.insertItem<ColorMapItem>();
    colormap_item->setDataItem(data_item);

    controller->setItem(colormap_item);

    auto color_map = TestUtils::GetPlottable<QCPColorMap>(custom_plot.get());

    EXPECT_EQ(color_map->gradient(), QCPColorGradient::gpPolar);

    auto combo = colormap_item->property<ComboProperty>(ColorMapItem::P_GRADIENT);
    combo.setValue("Hot");
    colormap_item->setProperty(ColorMapItem::P_GRADIENT, combo);
    EXPECT_EQ(color_map->gradient(), QCPColorGradient::gpHot);
}
