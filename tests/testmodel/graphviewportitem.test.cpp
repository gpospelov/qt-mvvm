// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "mockwidgets.h"
#include <mvvm/model/sessionmodel.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/standarditems/graphviewportitem.h>

using namespace ModelView;
using ::testing::_;

//! Testing AxesItems.

class GraphViewportItemTest : public ::testing::Test
{
public:
    ~GraphViewportItemTest();
};

GraphViewportItemTest::~GraphViewportItemTest() = default;

//! Initial state.

TEST_F(GraphViewportItemTest, initialState)
{
    GraphViewportItem item;
    EXPECT_EQ(item.xAxis()->modelType(), Constants::ViewportAxisItemType);
    EXPECT_EQ(item.yAxis()->modelType(), Constants::ViewportAxisItemType);
    EXPECT_EQ(item.graphItems().size(), 0);
}

//! Add graph to viewport.

TEST_F(GraphViewportItemTest, addItem)
{
    SessionModel model;

    auto viewport_item = model.insertItem<GraphViewportItem>();
    auto graph_item = model.insertItem<GraphItem>(viewport_item);
    auto data_item = model.insertItem<Data1DItem>();

    const std::vector<double> expected_values = {1.0, 2.0, 3.0};
    const std::vector<double> expected_centers = {0.5, 1.5, 2.5};
    data_item->setAxis<FixedBinAxisItem>(3, 0.0, 3.0);
    data_item->setValues(expected_values);

    graph_item->setDataItem(data_item);
    EXPECT_EQ(viewport_item->graphItems().size(), 1);

    // updating viewport to graph
    viewport_item->setViewportToContent();

    // x-axis of viewport should be set to FixedBinAxis of DataItem
    auto xaxis = viewport_item->xAxis();
    EXPECT_DOUBLE_EQ(xaxis->property<double>(ViewportAxisItem::P_MIN), expected_centers[0]);
    EXPECT_DOUBLE_EQ(xaxis->property<double>(ViewportAxisItem::P_MAX), expected_centers[2]);

    // y-axis of viewport should be set to min/max of expected_content
    auto yaxis = viewport_item->yAxis();
    auto [expected_amin, expected_amax] =
        std::minmax_element(std::begin(expected_values), std::end(expected_values));
    EXPECT_DOUBLE_EQ(yaxis->property<double>(ViewportAxisItem::P_MIN), *expected_amin);
    EXPECT_DOUBLE_EQ(yaxis->property<double>(ViewportAxisItem::P_MAX), *expected_amax);
}

//! Check signaling on set data item.

TEST_F(GraphViewportItemTest, onAddItem)
{
    SessionModel model;
    auto viewport_item = model.insertItem<GraphViewportItem>();

    MockWidgetForItem widget(viewport_item);

    const TagRow expected_tagrow{ViewportItem::T_ITEMS, 0};
    EXPECT_CALL(widget, onDataChange(_, _)).Times(0);
    EXPECT_CALL(widget, onPropertyChange(_, _)).Times(0);
    EXPECT_CALL(widget, onChildPropertyChange(_, _)).Times(0);
    EXPECT_CALL(widget, onItemInserted(viewport_item, expected_tagrow)).Times(1);
    EXPECT_CALL(widget, onAboutToRemoveItem(_, _)).Times(0);

    // triggering action
    model.insertItem<GraphItem>(viewport_item);
}

//! Check signaling on set data item.

TEST_F(GraphViewportItemTest, onSetDataItem)
{
    SessionModel model;
    auto viewport_item = model.insertItem<GraphViewportItem>();

    // setting upda tata item
    auto data_item = model.insertItem<Data1DItem>();
    const std::vector<double> expected_values = {1.0, 2.0, 3.0};
    const std::vector<double> expected_centers = {0.5, 1.5, 2.5};
    data_item->setAxis<FixedBinAxisItem>(3, 0.0, 3.0);
    data_item->setValues(expected_values);

    // inserting graph item
    auto graph_item = model.insertItem<GraphItem>(viewport_item);

    MockWidgetForItem widget(viewport_item);

    EXPECT_CALL(widget, onDataChange(_, _)).Times(0);
    EXPECT_CALL(widget, onPropertyChange(_, _)).Times(0);
    EXPECT_CALL(widget, onChildPropertyChange(graph_item, GraphItem::P_LINK)).Times(1);
    EXPECT_CALL(widget, onItemInserted(_, _)).Times(0);
    EXPECT_CALL(widget, onAboutToRemoveItem(_, _)).Times(0);

    // triggering action
    graph_item->setDataItem(data_item);
}

//! Add graph to viewport.

TEST_F(GraphViewportItemTest, setViewportToContentWithMargins)
{
    SessionModel model;

    auto viewport_item = model.insertItem<GraphViewportItem>();
    auto graph_item = model.insertItem<GraphItem>(viewport_item);
    auto data_item = model.insertItem<Data1DItem>();

    const std::vector<double> expected_values = {1.0, 2.0, 3.0};
    const std::vector<double> expected_centers = {0.5, 1.5, 2.5};
    data_item->setAxis<FixedBinAxisItem>(3, 0.0, 3.0);
    data_item->setValues(expected_values);

    graph_item->setDataItem(data_item);
    EXPECT_EQ(viewport_item->graphItems().size(), 1);

    // updating viewport to graph
    const double bottom{0.1}, top{0.1};
    viewport_item->setViewportToContent(0.0, top, 0.0, bottom);

    // x-axis of viewport should be set to FixedBinAxis of DataItem
    auto xaxis = viewport_item->xAxis();
    EXPECT_DOUBLE_EQ(xaxis->property<double>(ViewportAxisItem::P_MIN), expected_centers[0]);
    EXPECT_DOUBLE_EQ(xaxis->property<double>(ViewportAxisItem::P_MAX), expected_centers[2]);

    // y-axis of viewport should be set to min/max of expected_content
    auto yaxis = viewport_item->yAxis();
    auto [expected_amin, expected_amax] =
        std::minmax_element(std::begin(expected_values), std::end(expected_values));

    double expected_ymin = *expected_amin - (*expected_amax - *expected_amin) * bottom;
    double expected_ymax = *expected_amax + (*expected_amax - *expected_amin) * top;
    EXPECT_DOUBLE_EQ(yaxis->property<double>(ViewportAxisItem::P_MIN), expected_ymin);
    EXPECT_DOUBLE_EQ(yaxis->property<double>(ViewportAxisItem::P_MAX), expected_ymax);
}
