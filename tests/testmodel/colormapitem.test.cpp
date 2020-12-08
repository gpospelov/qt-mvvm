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
#include <mvvm/model/comboproperty.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/colormapitem.h>
#include <mvvm/standarditems/data2ditem.h>
#include <mvvm/standarditems/linkeditem.h>

using namespace ModelView;
using ::testing::_;

//! Testing ColorMapItem.

class ColorMapItemTest : public ::testing::Test
{
public:
    ~ColorMapItemTest();
};

ColorMapItemTest::~ColorMapItemTest() = default;

//! Initial state.

TEST_F(ColorMapItemTest, initialState)
{
    ColorMapItem item;
    EXPECT_TRUE(item.dataItem() == nullptr);
    EXPECT_TRUE(item.property<bool>(ColorMapItem::P_INTERPOLATION));
    EXPECT_EQ(item.property<ComboProperty>(ColorMapItem::P_GRADIENT).value(), "Polar");
}

//! Setting dataItem in model context.

TEST_F(ColorMapItemTest, setDataItem)
{
    SessionModel model;
    auto data_item = model.insertItem<Data2DItem>();
    auto colormap_item = model.insertItem<ColorMapItem>();

    colormap_item->setDataItem(data_item);

    EXPECT_EQ(colormap_item->dataItem(), data_item);
}

//! Check signaling on set data item.

TEST_F(ColorMapItemTest, onSetDataItem)
{
    SessionModel model;
    auto data_item = model.insertItem<Data2DItem>();
    auto colormap_item = model.insertItem<ColorMapItem>();

    MockWidgetForItem widget(colormap_item);

    EXPECT_CALL(widget, onDataChange(_, _)).Times(0);
    EXPECT_CALL(widget, onPropertyChange(colormap_item, ColorMapItem::P_LINK)).Times(1);
    EXPECT_CALL(widget, onChildPropertyChange(_, _)).Times(0);
    EXPECT_CALL(widget, onItemInserted(_, _)).Times(0);
    EXPECT_CALL(widget, onAboutToRemoveItem(_, _)).Times(0);

    // performing action
    colormap_item->setDataItem(data_item);
}
