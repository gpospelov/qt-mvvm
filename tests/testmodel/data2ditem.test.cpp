// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/standarditems/data2ditem.h"

#include "google_test.h"
#include "mockwidgets.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/standarditems/axisitems.h"
#include <stdexcept>

using namespace ModelView;
using ::testing::_;

//! Testing Data1DItem.

class Data2DItemTest : public ::testing::Test {
};

//! Initial state.

TEST_F(Data2DItemTest, initialState)
{
    Data2DItem item;

    EXPECT_EQ(item.xAxis(), nullptr);
    EXPECT_EQ(item.yAxis(), nullptr);
    EXPECT_EQ(item.content(), std::vector<double>());
    EXPECT_FALSE(item.hasData());
}

//! Checking the method ::setAxis.

TEST_F(Data2DItemTest, setAxes)
{
    Data2DItem item;

    const int nx = 5, ny = 3;
    item.setAxes(FixedBinAxisItem::create(nx, 0.0, 5.0), FixedBinAxisItem::create(ny, 0.0, 3.0));

    // checking type of the axis
    EXPECT_TRUE(item.item<FixedBinAxisItem>(Data2DItem::T_XAXIS) != nullptr);
    EXPECT_TRUE(item.item<FixedBinAxisItem>(Data2DItem::T_YAXIS) != nullptr);

    // checking bin values
    auto values = item.content();
    EXPECT_EQ(values.size(), nx * ny);
    EXPECT_EQ(std::accumulate(values.begin(), values.end(), 0), 0.0);
}

//! Checking the method ::setContent.

TEST_F(Data2DItemTest, setContent)
{
    Data2DItem item;

    // check that it is not possible to set content to uninitialized axis
    std::vector<double> expected_content = {1.0, 2.0};
    EXPECT_THROW(item.setContent(expected_content), std::runtime_error);

    const int nx = 1, ny = 2;
    item.setAxes(FixedBinAxisItem::create(nx, 0.0, 5.0), FixedBinAxisItem::create(ny, 0.0, 3.0));

    item.setContent(expected_content);
    EXPECT_EQ(item.content(), expected_content);
}

//! Checking the signals when axes changed.

TEST_F(Data2DItemTest, checkSignalsOnAxisChange)
{
    SessionModel model;
    auto item = model.insertItem<Data2DItem>();

    FixedBinAxisItem::create(3, 0.0, 3.0);

    MockWidgetForItem widget(item);

    EXPECT_CALL(widget, onDataChange(item, ItemDataRole::DATA)).Times(0);
    EXPECT_CALL(widget, onPropertyChange(_, Data2DItem::P_VALUES)).Times(1);
    EXPECT_CALL(widget, onChildPropertyChange(_, _)).Times(0);
    EXPECT_CALL(widget, onItemInserted(item, _)).Times(2);
    EXPECT_CALL(widget, onAboutToRemoveItem(_, _)).Times(0);

    // trigger change
    item->setAxes(FixedBinAxisItem::create(1, 0.0, 5.0), FixedBinAxisItem::create(3, 0.0, 3.0));
}

//! Checking the signals when content changed.

TEST_F(Data2DItemTest, checkSignalsOnContentChange)
{
    SessionModel model;
    auto item = model.insertItem<Data2DItem>();
    item->setAxes(FixedBinAxisItem::create(1, 0.0, 5.0), FixedBinAxisItem::create(3, 0.0, 3.0));

    MockWidgetForItem widget(item);

    EXPECT_CALL(widget, onDataChange(item, ItemDataRole::DATA)).Times(0);
    EXPECT_CALL(widget, onPropertyChange(_, Data2DItem::P_VALUES)).Times(1);
    EXPECT_CALL(widget, onChildPropertyChange(_, _)).Times(0);
    EXPECT_CALL(widget, onItemInserted(_, _)).Times(0);
    EXPECT_CALL(widget, onAboutToRemoveItem(_, _)).Times(0);

    // trigger change
    item->setContent(std::vector<double>{1.0, 2.0, 3.0});
}
