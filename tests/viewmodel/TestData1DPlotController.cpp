#include "data1ditem.h"
#include "data1dplotcontroller.h"
#include "google_test.h"
#include "qcustomplot.h"
#include "sessionmodel.h"
#include <algorithm>

using namespace ModelView;

namespace
{

//! Returns vector representing either bin centers or values on QCPGraph.
template <typename T> std::vector<double> get_values(const QCPGraph* graph, T operand)
{
    std::vector<double> result;
    auto graph_data = *graph->data();
    std::transform(std::begin(graph_data), std::end(graph_data), std::back_inserter(result),
                   [operand](const auto& point) { return operand(point); });
    return result;
}

} // namespace

//! Testing Data1DPlotController.

class TestData1DPlotController : public ::testing::Test
{
public:
    ~TestData1DPlotController();

    //! Returns vector representing bin centers on QCPgraph.
    std::vector<double> binCenters(const QCPGraph* graph)
    {
        return get_values(graph, [](auto x) { return x.key; });
    }

    //! Returns vector representing y-values on QCPgraph.
    std::vector<double> binValues(const QCPGraph* graph)
    {
        return get_values(graph, [](auto x) { return x.value; });
    }
};

TestData1DPlotController::~TestData1DPlotController() = default;

//! Initial state.

TEST_F(TestData1DPlotController, initialState)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    auto graph = custom_plot->addGraph();

    Data1DPlotController controller(graph);
    EXPECT_EQ(controller.currentItem(), nullptr);
}

//! Testing graph points update.

TEST_F(TestData1DPlotController, dataPoints)
{
    // creating custom plot and empty graph on it
    auto custom_plot = std::make_unique<QCustomPlot>();
    auto graph = custom_plot->addGraph();

    // creating data item with single point
    SessionModel model;
    auto data_item = dynamic_cast<Data1DItem*>(model.insertNewItem(Constants::Data1DItemType));
    data_item->setFixedBinAxis(1, 1.0, 2.0);

    // creating controller and point it to Data1DItem
    Data1DPlotController controller(graph);
    controller.setItem(data_item);

    // checking that QCPGraph now has data points as in Data1DItem
    EXPECT_EQ(data_item->binCenters(), binCenters(graph));
    EXPECT_EQ(data_item->binValues(), binValues(graph));

    // setting item to nullptr, points on graph should disappear
    controller.setItem(nullptr);
    EXPECT_EQ(std::vector<double>(), binCenters(graph));
    EXPECT_EQ(std::vector<double>(), binValues(graph));
}

//! Testing two graph scenario.

TEST_F(TestData1DPlotController, twoDataItems)
{
    // creating custom plot and empty graph on it
    auto custom_plot = std::make_unique<QCustomPlot>();
    auto graph = custom_plot->addGraph();

    // creating data item with single point
    SessionModel model;
    auto data_item1 = dynamic_cast<Data1DItem*>(model.insertNewItem(Constants::Data1DItemType));
    data_item1->setFixedBinAxis(1, 1.0, 2.0);
    auto data_item2 = dynamic_cast<Data1DItem*>(model.insertNewItem(Constants::Data1DItemType));
    data_item2->setFixedBinAxis(2, 0.0, 2.0);

    // creating controller and point it to Data1DItem
    Data1DPlotController controller(graph);
    controller.setItem(data_item1);

    // checking that QCPGraph now has data points as in Data1DItem
    EXPECT_EQ(data_item1->binCenters(), binCenters(graph));
    EXPECT_EQ(data_item1->binValues(), binValues(graph));

    // setting item to nullptr, points on graph should disappear
    controller.setItem(data_item2);
    EXPECT_EQ(data_item2->binCenters(), binCenters(graph));
    EXPECT_EQ(data_item2->binValues(), binValues(graph));
}
