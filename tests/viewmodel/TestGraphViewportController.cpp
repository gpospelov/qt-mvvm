#include "google_test.h"
#include "qcustomplot.h"
#include "graphviewportplotcontroller.h"
#include "graphviewportitem.h"
#include "sessionmodel.h"

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
