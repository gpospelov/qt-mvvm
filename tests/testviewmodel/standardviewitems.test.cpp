// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <QColor>
#include <memory>
#include <mvvm/model/sessionitem.h>
#include <mvvm/viewmodel/standardviewitems.h>
#include <stdexcept>

using namespace ModelView;

class StandardViewItemsTest : public ::testing::Test
{
public:
    ~StandardViewItemsTest();
};

StandardViewItemsTest::~StandardViewItemsTest() = default;

// ----------------------------------------------------------------------------
// Tests for ViewLabelItem
// ----------------------------------------------------------------------------

TEST_F(StandardViewItemsTest, ViewLabelItem_initialState)
{
    SessionItem item;
    ViewLabelItem viewItem(&item);
    EXPECT_EQ(viewItem.item(), &item);
    EXPECT_EQ(viewItem.item_role(), ItemDataRole::DISPLAY);
}

//! ViewLabelItem::data method
//! Checks that the data method is correctly forwarded to underlying SessionItem.

TEST_F(StandardViewItemsTest, ViewLabelItem_data)
{
    // create SessionItem with data on board
    SessionItem item;
    const std::string expected("Layer");
    EXPECT_TRUE(item.setData(expected, ItemDataRole::DISPLAY));

    // initialize viewItem with sessionItem and check the data
    ViewLabelItem viewItem(&item);
    EXPECT_EQ(Utils::toCustomVariant(viewItem.data(Qt::EditRole)), QVariant::fromValue(expected));
    EXPECT_EQ(Utils::toCustomVariant(viewItem.data(Qt::DisplayRole)),
              QVariant::fromValue(expected));
}

//! ViewLabelItem::setData
//! Checks that the setData method is correctly forwarded to underlying SessionItem.

TEST_F(StandardViewItemsTest, ViewLabelItem_setData)
{
    // create SessionItem with data on board
    SessionItem item;
    const std::string expected("Layer");
    EXPECT_TRUE(item.setData(expected, ItemDataRole::DISPLAY));

    // initialize viewItem with sessionItem and set the data
    ViewLabelItem viewItem(&item);
    QVariant new_data("MultiLayer");
    EXPECT_TRUE(viewItem.setData(new_data, Qt::EditRole));
    EXPECT_EQ(viewItem.data(Qt::DisplayRole), new_data); // new data
    EXPECT_EQ(viewItem.data(Qt::EditRole), new_data);    // new data

    // SessionItem itself should have new data
    EXPECT_EQ(item.data<QVariant>(ItemDataRole::DISPLAY),
              Utils::toCustomVariant(new_data)); // new data

    // it is not allowed to set another type of data to ViewLabelItem
    QVariant not_allowed_value(42);
    EXPECT_THROW(viewItem.setData(not_allowed_value, Qt::EditRole), std::runtime_error);
}

//! Testing ViewLabelItem::flags.

TEST_F(StandardViewItemsTest, ViewLabelItem_flags)
{
    SessionItem item;
    const std::string expected("Layer");
    EXPECT_TRUE(item.setData(expected, ItemDataRole::DISPLAY));

    ViewLabelItem viewItem(&item);
    EXPECT_FALSE(viewItem.flags() & Qt::ItemIsEditable);
}

//! Testing tooltip tole.

TEST_F(StandardViewItemsTest, ViewLabelItem_toolTipRole)
{
    SessionItem item;

    ViewLabelItem viewItem(&item);
    EXPECT_FALSE(viewItem.data(Qt::ToolTipRole).isValid());

    item.setToolTip("abc");
    EXPECT_EQ(viewItem.data(Qt::ToolTipRole).toString(), QString("abc"));
}

// ----------------------------------------------------------------------------
// Tests for ViewDataItem
// ----------------------------------------------------------------------------

TEST_F(StandardViewItemsTest, ViewDataItem_initialState)
{
    SessionItem item;
    ViewDataItem viewItem(&item);
    EXPECT_EQ(viewItem.item(), &item);
    EXPECT_EQ(viewItem.item_role(), ItemDataRole::DATA);
}

//! ViewDataItem::data method for double values.
//! Checks that the data method is correctly forwarded to underlying SessionItem.

TEST_F(StandardViewItemsTest, ViewDataItem_dataForDouble)
{
    // create SessionItem with data on board
    SessionItem item;
    QVariant expected(42.0);
    EXPECT_TRUE(item.setData(expected));

    // initialize viewItem with sessionItem and check the data
    ViewDataItem viewItem(&item);
    EXPECT_EQ(viewItem.data(Qt::EditRole), expected);
    EXPECT_EQ(viewItem.data(Qt::DisplayRole), expected);
}

//! ViewDataItem::setData for double values.
//! Checks that the setData method is correctly forwarded to underlying SessionItem.

TEST_F(StandardViewItemsTest, ViewDataItem_setDataForDouble)
{
    // create SessionItem with data on board
    SessionItem item;
    QVariant expected(42.0);
    EXPECT_TRUE(item.setData(expected));

    // initialize viewItem with sessionItem and set the data
    ViewDataItem viewItem(&item);
    QVariant new_data(43.0);
    EXPECT_TRUE(viewItem.setData(new_data, Qt::EditRole));
    EXPECT_EQ(viewItem.data(Qt::DisplayRole), new_data); // new data
    EXPECT_EQ(viewItem.data(Qt::EditRole), new_data);    // new data

    // SessionItem itself should have new data
    EXPECT_EQ(item.data<QVariant>(), new_data); // new data

    // it is not allowed to set another type of data to ViewDataItem
    QVariant not_allowed_value("Layer");
    EXPECT_THROW(viewItem.setData(not_allowed_value, Qt::EditRole), std::runtime_error);
}

//! ViewDataItem::setData for double values.
//! Checks that setting of same data returns false.

TEST_F(StandardViewItemsTest, ViewDataItem_setSameData)
{
    // create SessionItem with data on board
    SessionItem item;
    QVariant expected(42.0);
    EXPECT_TRUE(item.setData(expected));

    // initialize viewItem with sessionItem and set the data
    ViewDataItem viewItem(&item);
    QVariant new_data(42.0);
    EXPECT_FALSE(viewItem.setData(new_data, Qt::EditRole));
    EXPECT_EQ(viewItem.data(Qt::EditRole), new_data); // new data
}

//! ViewDataItem::data method for QColor.
//! Checks that the data method is correctly forwarded to underlying SessionItem.

TEST_F(StandardViewItemsTest, ViewDataItem_dataForColor)
{
    // create SessionItem with data on board
    SessionItem item;
    QVariant expected = QVariant::fromValue(QColor(Qt::green));
    EXPECT_TRUE(item.setData(expected));

    ViewDataItem viewItem(&item);
    EXPECT_EQ(viewItem.data(Qt::EditRole), expected);
    EXPECT_EQ(viewItem.data(Qt::DisplayRole), expected);
    EXPECT_EQ(viewItem.data(Qt::DecorationRole), expected);
}

//! ViewDataItem::setData for QColor.
//! Checks that the setData method is correctly forwarded to underlying SessionItem.

TEST_F(StandardViewItemsTest, ViewDataItem_setDataForColor)
{
    // create SessionItem with data on board
    SessionItem item;
    QVariant expected = QVariant::fromValue(QColor(Qt::green));
    EXPECT_TRUE(item.setData(expected));

    // initialize viewItem with sessionItem and set the data
    ViewDataItem viewItem(&item);
    QVariant new_data = QVariant::fromValue(QColor(Qt::red));
    EXPECT_TRUE(viewItem.setData(new_data, Qt::EditRole));
    EXPECT_EQ(viewItem.data(Qt::DisplayRole), new_data);    // new data
    EXPECT_EQ(viewItem.data(Qt::EditRole), new_data);       // new data
    EXPECT_EQ(viewItem.data(Qt::DecorationRole), new_data); // new data

    // SessionItem itself should have new data
    EXPECT_EQ(item.data<QVariant>(), new_data); // new data

    // it is not allowed to set another type of data to ViewDataItem
    QVariant not_allowed_value("Layer");
    EXPECT_THROW(viewItem.setData(not_allowed_value, Qt::EditRole), std::runtime_error);
}

//! Testing ViewLabelItem::flags.

TEST_F(StandardViewItemsTest, ViewDataItem_flags)
{
    SessionItem item;
    QVariant expected = QVariant::fromValue(std::string("Layer"));
    EXPECT_TRUE(item.setData(expected, ItemDataRole::DATA));

    ViewDataItem viewItem(&item);
    EXPECT_TRUE(viewItem.flags() & Qt::ItemIsEditable);
}

//! Testing tooltip tole.

TEST_F(StandardViewItemsTest, ViewDataItem_toolTipRole)
{
    SessionItem item;

    ViewDataItem viewItem(&item);
    EXPECT_FALSE(viewItem.data(Qt::ToolTipRole).isValid());

    item.setToolTip("abc");
    EXPECT_EQ(viewItem.data(Qt::ToolTipRole).toString(), QString("abc"));
}

//! Behavior of ViewDataItem with SessionItem which initially contains invalid data.
//! It should be possible to set data after.

TEST_F(StandardViewItemsTest, ViewDataItem_invalidTheValidData)
{
    SessionItem item;
    ViewDataItem viewItem(&item);

    // initially data is invalid, and non-editable
    EXPECT_FALSE(viewItem.flags() & Qt::ItemIsEditable);
    EXPECT_FALSE(viewItem.data(Qt::EditRole).isValid());

    // current behavior that setting data is still possible
    EXPECT_TRUE(viewItem.setData(QVariant::fromValue(42.0), Qt::EditRole));

    // setting data to original item
    item.setData(43.0);

    // data became editable via ViewDataItem
    EXPECT_TRUE(viewItem.flags() & Qt::ItemIsEditable);
    EXPECT_EQ(viewItem.data(Qt::EditRole), QVariant::fromValue(43.0));
}
