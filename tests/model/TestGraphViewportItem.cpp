#include "MockWidgets.h"
#include "axisitems.h"
#include "data1ditem.h"
#include "google_test.h"
#include "graphitem.h"
#include "graphviewportitem.h"
#include "sessionmodel.h"

using namespace ModelView;
using ::testing::_;

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

    auto viewport_item = model.insertItem<GraphViewportItem>();
    auto graph_item = model.insertItem<GraphItem>(viewport_item);
    auto data_item = model.insertItem<Data1DItem>();

    const std::vector<double> expected_content = {1.0, 2.0, 3.0};
    const std::vector<double> expected_centers = {0.5, 1.5, 2.5};
    data_item->setAxis(FixedBinAxisItem::create(3, 0.0, 3.0));
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

//! Check signaling on set data item.

TEST_F(TestGraphViewportItem, onAddItem)
{
    SessionModel model;
    auto viewport_item = model.insertItem<GraphViewportItem>();

    MockWidgetForItem widget(viewport_item);

    EXPECT_CALL(widget, onDataChange(_, _)).Times(0);
    EXPECT_CALL(widget, onPropertyChange(_, _)).Times(0);
    EXPECT_CALL(widget, onChildPropertyChange(_, _)).Times(0);
    EXPECT_CALL(widget, onRowInserted(viewport_item, GraphViewportItem::T_GRAPHS, 0)).Times(1);
    EXPECT_CALL(widget, onRowAboutToBeRemoved(_, _, _)).Times(0);

    // triggering action
    model.insertItem<GraphItem>(viewport_item);
}

//! Check signaling on set data item.

TEST_F(TestGraphViewportItem, onSetDataItem)
{
    SessionModel model;
    auto viewport_item = model.insertItem<GraphViewportItem>();

    // setting upda tata item
    auto data_item = model.insertItem<Data1DItem>();
    const std::vector<double> expected_content = {1.0, 2.0, 3.0};
    const std::vector<double> expected_centers = {0.5, 1.5, 2.5};
    data_item->setAxis(FixedBinAxisItem::create(3, 0.0, 3.0));
    data_item->setContent(expected_content);

    // inserting graph item
    auto graph_item = model.insertItem<GraphItem>(viewport_item);

    MockWidgetForItem widget(viewport_item);

    EXPECT_CALL(widget, onDataChange(_, _)).Times(0);
    EXPECT_CALL(widget, onPropertyChange(_, _)).Times(0);
    EXPECT_CALL(widget, onChildPropertyChange(graph_item, GraphItem::P_LINK)).Times(1);
    EXPECT_CALL(widget, onRowInserted(_, _, _)).Times(0);
    EXPECT_CALL(widget, onRowAboutToBeRemoved(_, _, _)).Times(0);

    // triggering action
    graph_item->setDataItem(data_item);
}
