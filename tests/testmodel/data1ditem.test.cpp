// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "MockWidgets.h"
#include "google_test.h"
#include <mvvm/model/sessionmodel.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/data1ditem.h>

using namespace ModelView;
using ::testing::_;

//! Testing Data1DItem.

class Data1DItemTest : public ::testing::Test
{
public:
    ~Data1DItemTest();
};

Data1DItemTest::~Data1DItemTest() = default;

//! Initial state.

TEST_F(Data1DItemTest, initialState)
{
    Data1DItem item;

    EXPECT_EQ(item.getItem(Data1DItem::T_AXIS), nullptr);
    EXPECT_EQ(item.binCenters(), std::vector<double>());
    EXPECT_EQ(item.binValues(), std::vector<double>());
    EXPECT_TRUE(item.hasData());
    EXPECT_TRUE(item.data<std::vector<double>>().empty());
}

//! Checking the method ::setFixedBinAxis.

TEST_F(Data1DItemTest, setFixedBinAxis)
{
    Data1DItem item;

    item.setAxis(FixedBinAxisItem::create(5, 0.0, 5.0));

    // check type of the axis
    EXPECT_TRUE(item.item<FixedBinAxisItem>(Data1DItem::T_AXIS) != nullptr);

    // check bin centers and values
    std::vector<double> expected_centers = {0.5, 1.5, 2.5, 3.5, 4.5};
    EXPECT_EQ(item.binCenters(), expected_centers);
    std::vector<double> expected_values = std::vector<double>(expected_centers.size(), 0.0);
    EXPECT_EQ(item.binValues(), expected_values);

    // setting another axis
    item.setAxis(FixedBinAxisItem::create(1, 1.0, 2.0));
    expected_centers = {1.5};
    EXPECT_EQ(item.binCenters(), expected_centers);
    expected_values = {0.0};
    EXPECT_EQ(item.binValues(), expected_values);
}

//! Checking the method ::setContent.

TEST_F(Data1DItemTest, setContent)
{
    Data1DItem item;

    // check that it is not possible to set content to uninitialized axis
    std::vector<double> expected_content = {1.0, 2.0, 3.0};
    EXPECT_THROW(item.setContent(expected_content), std::runtime_error);

    item.setAxis(FixedBinAxisItem::create(3, 0.0, 3.0));
    item.setContent(expected_content);
    EXPECT_EQ(item.binValues(), expected_content);
}

//! Checking the signals when axes changed.

TEST_F(Data1DItemTest, checkSignalsOnAxisChange)
{
    SessionModel model;
    auto item = model.insertItem<Data1DItem>();

    MockWidgetForItem widget(item);

    const TagRow expected_tagrow{Data1DItem::T_AXIS, 0};
    EXPECT_CALL(widget, onDataChange(item, ItemDataRole::DATA)).Times(1); // values should change
    EXPECT_CALL(widget, onPropertyChange(_, _)).Times(0);
    EXPECT_CALL(widget, onChildPropertyChange(_, _)).Times(0);
    EXPECT_CALL(widget, onItemInserted(item, expected_tagrow)).Times(1);
    EXPECT_CALL(widget, onAboutToRemoveItem(_, _)).Times(0);

    // trigger change
    item->setAxis(FixedBinAxisItem::create(3, 0.0, 3.0));
}

//! Checking the signals when content changed.

TEST_F(Data1DItemTest, checkSignalsOnContentChange)
{
    SessionModel model;
    auto item = model.insertItem<Data1DItem>();
    item->setAxis(FixedBinAxisItem::create(3, 0.0, 3.0));

    MockWidgetForItem widget(item);

    EXPECT_CALL(widget, onDataChange(item, ItemDataRole::DATA)).Times(1); // values should change
    EXPECT_CALL(widget, onPropertyChange(_, _)).Times(0);
    EXPECT_CALL(widget, onChildPropertyChange(_, _)).Times(0);
    EXPECT_CALL(widget, onItemInserted(_, _)).Times(0);
    EXPECT_CALL(widget, onAboutToRemoveItem(_, _)).Times(0);

    // trigger change
    item->setContent(std::vector<double>{1.0, 2.0, 3.0});
}
