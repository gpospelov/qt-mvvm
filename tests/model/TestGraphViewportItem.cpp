#include "axisitems.h"
#include "data1ditem.h"
#include "google_test.h"
#include "graphitem.h"
#include "graphviewportitem.h"
#include "sessionmodel.h"

using namespace ModelView;

//! Testing AxesItems.

class TestGraphViewportItem : public ::testing::Test
{
public:
    ~TestGraphViewportItem();
};

TestGraphViewportItem::~TestGraphViewportItem() = default;

//! Initial state.

TEST_F(TestGraphViewportItem, initialState)
{
    GraphViewportItem item;
    EXPECT_EQ(item.xAxis()->modelType(), Constants::ViewportAxisType);
    EXPECT_EQ(item.yAxis()->modelType(), Constants::ViewportAxisType);
    EXPECT_EQ(item.graphItems().size(), 0);
}

//! Add graph to viewport.

TEST_F(TestGraphViewportItem, addItem)
{
    SessionModel model;

    auto viewport_item =
        dynamic_cast<GraphViewportItem*>(model.insertNewItem(Constants::GraphViewportItemType));
    auto graph_item =
        dynamic_cast<GraphItem*>(model.insertNewItem(Constants::GraphItemType, viewport_item));
    auto data_item = dynamic_cast<Data1DItem*>(model.insertNewItem(Constants::Data1DItemType));

    const std::vector<double> expected_content = {1.0, 2.0, 3.0};
    const std::vector<double> expected_centers = {0.5, 1.5, 2.5};
    data_item->setFixedBinAxis(3, 0.0, 3.0);
    data_item->setContent(expected_content);

    graph_item->setDataItem(data_item);
    EXPECT_EQ(viewport_item->graphItems().size(), 1);

    // updating viewport to graph
    viewport_item->update_viewport();

    // x-axis of viewport should be set to FixedBinAxis of DataItem
    auto xaxis = viewport_item->xAxis();
    EXPECT_DOUBLE_EQ(xaxis->property(ViewportAxisItem::P_MIN).toDouble(), expected_centers[0]);
    EXPECT_DOUBLE_EQ(xaxis->property(ViewportAxisItem::P_MAX).toDouble(), expected_centers[2]);

    // y-axis of viewport should be set to min/max*1.1 of expected_content
    auto yaxis = viewport_item->yAxis();
    auto [expected_amin, expected_amax] =
        std::minmax_element(std::begin(expected_content), std::end(expected_content));
    EXPECT_DOUBLE_EQ(yaxis->property(ViewportAxisItem::P_MIN).toDouble(), *expected_amin);
    EXPECT_DOUBLE_EQ(yaxis->property(ViewportAxisItem::P_MAX).toDouble(), *expected_amax);
}
