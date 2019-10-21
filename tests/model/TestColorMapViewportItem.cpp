#include "MockWidgets.h"
#include "axisitems.h"
#include "colormapitem.h"
#include "colormapviewportitem.h"
#include "data2ditem.h"
#include "google_test.h"
#include "sessionmodel.h"

using namespace ModelView;
using ::testing::_;

//! Testing AxesItems.

class TestColorMapViewportItem : public ::testing::Test
{
public:
    ~TestColorMapViewportItem();
};

TestColorMapViewportItem::~TestColorMapViewportItem() = default;

//! Initial state.

TEST_F(TestColorMapViewportItem, initialState)
{
    ColorMapViewportItem viewport;
    EXPECT_EQ(viewport.xAxis()->modelType(), Constants::ViewportAxisItemType);
    EXPECT_EQ(viewport.yAxis()->modelType(), Constants::ViewportAxisItemType);
    EXPECT_EQ(viewport.zAxis()->modelType(), Constants::ViewportAxisItemType);
    EXPECT_EQ(viewport.items<ColorMapItem>(ColorMapViewportItem::T_ITEMS).size(), 0);
}

//! Add graph to viewport.

TEST_F(TestColorMapViewportItem, addItem)
{
    SessionModel model;

    auto viewport_item = model.insertItem<ColorMapViewportItem>();
    auto colormap_item = model.insertItem<ColorMapItem>(viewport_item);
    auto data_item = model.insertItem<Data2DItem>();

    data_item->setAxes(FixedBinAxisItem::create(2, 0.0, 2.0),
                       FixedBinAxisItem::create(3, 0.0, 3.0));
    const std::vector<double> expected_content = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    data_item->setContent(expected_content);

    colormap_item->setDataItem(data_item);
    EXPECT_EQ(viewport_item->items<ColorMapItem>(ColorMapViewportItem::T_ITEMS).size(), 1);

    // updating viewport to graph
    viewport_item->update_viewport();

    // x-axis of viewport should be set to min/max content
    auto [zmin, zmax] = viewport_item->zAxis()->range();
    EXPECT_DOUBLE_EQ(zmin, 1.0);
    EXPECT_DOUBLE_EQ(zmax, 6.0);
}

//! Check signaling on set data item.

TEST_F(TestColorMapViewportItem, onAddItem)
{
    SessionModel model;
    auto viewport_item = model.insertItem<ColorMapViewportItem>();

    MockWidgetForItem widget(viewport_item);

    EXPECT_CALL(widget, onDataChange(_, _)).Times(0);
    EXPECT_CALL(widget, onPropertyChange(_, _)).Times(0);
    EXPECT_CALL(widget, onChildPropertyChange(_, _)).Times(0);
    EXPECT_CALL(widget, onRowInserted(viewport_item, ViewportItem::T_ITEMS, 0)).Times(1);
    EXPECT_CALL(widget, onRowAboutToBeRemoved(_, _, _)).Times(0);

    // triggering action
    model.insertItem<ColorMapItem>(viewport_item);
}

//! Check signaling on set data item.

TEST_F(TestColorMapViewportItem, onSetDataItem)
{
    SessionModel model;
    auto viewport_item = model.insertItem<ColorMapViewportItem>();

    // setting upda tata item
    auto data_item = model.insertItem<Data2DItem>();

    data_item->setAxes(FixedBinAxisItem::create(2, 0.0, 2.0),
                       FixedBinAxisItem::create(3, 0.0, 3.0));
    const std::vector<double> expected_content = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    data_item->setContent(expected_content);

    // inserting graph item
    auto colormap_item = model.insertItem<ColorMapItem>(viewport_item);

    MockWidgetForItem widget(viewport_item);

    EXPECT_CALL(widget, onDataChange(_, _)).Times(0);
    EXPECT_CALL(widget, onPropertyChange(_, _)).Times(0);
    EXPECT_CALL(widget, onChildPropertyChange(colormap_item, ColorMapItem::P_LINK)).Times(1);
    EXPECT_CALL(widget, onRowInserted(_, _, _)).Times(0);
    EXPECT_CALL(widget, onRowAboutToBeRemoved(_, _, _)).Times(0);

    // triggering action
    colormap_item->setDataItem(data_item);
}
