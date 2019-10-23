#include "google_test.h"
#include "qcustomplot.h"
#include "colormapplotcontroller.h"
#include "colormapitem.h"
#include "sessionmodel.h"
#include "data2ditem.h"
#include "axisitems.h"
#include "customplot_test_utils.h"
#include <QSignalSpy>

using namespace ModelView;

//! Testing ColorMapPlotController.

class TestColorMapPlotController : public ::testing::Test
{
public:
    ~TestColorMapPlotController();
};

TestColorMapPlotController::~TestColorMapPlotController() = default;

//! Initial state.

TEST_F(TestColorMapPlotController, initialState)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    ColorMapPlotController controller(custom_plot.get());
    EXPECT_EQ(controller.currentItem(), nullptr);
    EXPECT_EQ(custom_plot->plottableCount(), 0);
}

//! Setting ColorMapItem with data and checking that QCPColorMap appeared among plottables.

TEST_F(TestColorMapPlotController, setItem)
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

