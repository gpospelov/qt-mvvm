#include "google_test.h"
#include "qcustomplot.h"
#include "graphitemcontroller.h"
#include "graphitem.h"
#include "sessionmodel.h"
#include "data1ditem.h"
#include "customplot_test_utils.h"
#include <QSignalSpy>

using namespace ModelView;

//! Testing AxisPlotControllers.

class TestGraphItemController : public ::testing::Test
{
public:
    ~TestGraphItemController();
};

TestGraphItemController::~TestGraphItemController() = default;

//! Initial state.

TEST_F(TestGraphItemController, setItem)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    GraphItemController controller(custom_plot.get());
    EXPECT_EQ(custom_plot->graphCount(), 0);

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
