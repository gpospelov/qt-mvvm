#include "google_test.h"
#include <mvvm/standarditems/colormapitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/standarditems/data2ditem.h>
#include "MockWidgets.h"
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/linkeditem.h>

using namespace ModelView;
using ::testing::_;

//! Testing ColorMapItem.

class TestColorMapItem : public ::testing::Test
{
public:
    ~TestColorMapItem();
};

TestColorMapItem::~TestColorMapItem() = default;

//! Initial state.

TEST_F(TestColorMapItem, initialState)
{
    ColorMapItem item;
    EXPECT_TRUE(item.dataItem() == nullptr);
    EXPECT_TRUE(item.property(ColorMapItem::P_INTERPOLATION).value<bool>());
}

//! Setting dataItem in model context.

TEST_F(TestColorMapItem, setDataItem)
{
    SessionModel model;
    auto data_item = model.insertItem<Data2DItem>();
    auto colormap_item = model.insertItem<ColorMapItem>();

    colormap_item->setDataItem(data_item);

    EXPECT_EQ(colormap_item->dataItem(), data_item);
}

//! Check signaling on set data item.

TEST_F(TestColorMapItem, onSetDataItem)
{
    SessionModel model;
    auto data_item = model.insertItem<Data2DItem>();
    auto colormap_item = model.insertItem<ColorMapItem>();

    MockWidgetForItem widget(colormap_item);

    EXPECT_CALL(widget, onDataChange(_, _)).Times(0);
    EXPECT_CALL(widget, onPropertyChange(colormap_item, ColorMapItem::P_LINK)).Times(1);
    EXPECT_CALL(widget, onChildPropertyChange(_, _)).Times(0);
    EXPECT_CALL(widget, onRowInserted(_, _, _)).Times(0);
    EXPECT_CALL(widget, onRowAboutToBeRemoved(_, _, _)).Times(0);

    // performing action
    colormap_item->setDataItem(data_item);
}
