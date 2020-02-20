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
#include <mvvm/viewmodel/refviewitems.h>

using namespace ModelView;

class RefViewItemsTest : public ::testing::Test
{
public:
    ~RefViewItemsTest();
};

RefViewItemsTest::~RefViewItemsTest() = default;

// ----------------------------------------------------------------------------
// Tests for ViewLabelItem
// ----------------------------------------------------------------------------

TEST_F(RefViewItemsTest, ViewLabelItem_initialState)
{
    auto item = std::make_unique<SessionItem>();
    RefViewLabelItem viewItem(item.get());
    EXPECT_EQ(viewItem.item(), item.get());
    EXPECT_EQ(viewItem.item_role(), ItemDataRole::DISPLAY);
}

//! ViewLabelItem::data method
//! Checks that the data method is correctly forwarded to underlying SessionItem.

TEST_F(RefViewItemsTest, ViewLabelItem_data)
{
    // create SessionItem with data on board
    auto item = std::make_unique<SessionItem>();
    QVariant expected = QVariant::fromValue(std::string("Layer"));
    EXPECT_TRUE(item->setData(expected, ItemDataRole::DISPLAY));

    // initialize viewItem with sessionItem and check the data
    RefViewLabelItem viewItem(item.get());
    EXPECT_EQ(Utils::toCustomVariant(viewItem.data(Qt::EditRole)), expected);
    EXPECT_EQ(Utils::toCustomVariant(viewItem.data(Qt::DisplayRole)), expected);
}

//! ViewLabelItem::setData
//! Checks that the setData method is correctly forwarded to underlying SessionItem.

TEST_F(RefViewItemsTest, ViewLabelItem_setData)
{
    // create SessionItem with data on board
    auto item = std::make_unique<SessionItem>();
    QVariant expected = QVariant::fromValue(std::string("Layer"));
    EXPECT_TRUE(item->setData(expected, ItemDataRole::DISPLAY));

    // initialize viewItem with sessionItem and set the data
    RefViewLabelItem viewItem(item.get());
    QVariant new_data("MultiLayer");
    EXPECT_TRUE(viewItem.setData(new_data, Qt::EditRole));
    EXPECT_EQ(viewItem.data(Qt::DisplayRole), new_data); // new data
    EXPECT_EQ(viewItem.data(Qt::EditRole), new_data);    // new data

    // SessionItem itself should have new data
    EXPECT_EQ(item->data(ItemDataRole::DISPLAY), Utils::toCustomVariant(new_data)); // new data

    // it is not allowed to set another type of data to ViewLabelItem
    QVariant not_allowed_value(42);
    EXPECT_THROW(viewItem.setData(not_allowed_value, Qt::EditRole), std::runtime_error);
}

//! Testing ViewLabelItem::flags.

TEST_F(RefViewItemsTest, ViewLabelItem_flags)
{
    SessionItem item;
    QVariant expected = QVariant::fromValue(std::string("Layer"));
    EXPECT_TRUE(item.setData(expected, ItemDataRole::DISPLAY));

    RefViewLabelItem viewItem(&item);
    EXPECT_FALSE(viewItem.flags() & Qt::ItemIsEditable);
}

// ----------------------------------------------------------------------------
// Tests for ViewDataItem
// ----------------------------------------------------------------------------

TEST_F(RefViewItemsTest, ViewDataItem_initialState)
{
    std::unique_ptr<SessionItem> item(new SessionItem);

    RefViewDataItem viewItem(item.get());
    EXPECT_EQ(viewItem.item(), item.get());
    EXPECT_EQ(viewItem.item_role(), ItemDataRole::DATA);
}

//! ViewDataItem::data method for double values.
//! Checks that the data method is correctly forwarded to underlying SessionItem.

TEST_F(RefViewItemsTest, ViewDataItem_dataForDouble)
{
    // create SessionItem with data on board
    auto item = std::make_unique<SessionItem>();
    QVariant expected(42.0);
    EXPECT_TRUE(item->setData(expected));

    // initialize viewItem with sessionItem and check the data
    RefViewDataItem viewItem(item.get());
    EXPECT_EQ(viewItem.data(Qt::EditRole), expected);
    EXPECT_EQ(viewItem.data(Qt::DisplayRole), expected);
}

//! ViewDataItem::setData for double values.
//! Checks that the setData method is correctly forwarded to underlying SessionItem.

TEST_F(RefViewItemsTest, ViewDataItem_setDataForDouble)
{
    // create SessionItem with data on board
    auto item = std::make_unique<SessionItem>();
    QVariant expected(42.0);
    EXPECT_TRUE(item->setData(expected));

    // initialize viewItem with sessionItem and set the data
    RefViewDataItem viewItem(item.get());
    QVariant new_data(43.0);
    EXPECT_TRUE(viewItem.setData(new_data, Qt::EditRole));
    EXPECT_EQ(viewItem.data(Qt::DisplayRole), new_data); // new data
    EXPECT_EQ(viewItem.data(Qt::EditRole), new_data);    // new data

    // SessionItem itself should have new data
    EXPECT_EQ(item->data(), new_data); // new data

    // it is not allowed to set another type of data to ViewDataItem
    QVariant not_allowed_value("Layer");
    EXPECT_THROW(viewItem.setData(not_allowed_value, Qt::EditRole), std::runtime_error);
}

//! ViewDataItem::setData for double values.
//! Checks that setting of same data returns false.

TEST_F(RefViewItemsTest, ViewDataItem_setSameData)
{
    // create SessionItem with data on board
    auto item = std::make_unique<SessionItem>();
    QVariant expected(42.0);
    EXPECT_TRUE(item->setData(expected));

    // initialize viewItem with sessionItem and set the data
    RefViewDataItem viewItem(item.get());
    QVariant new_data(42.0);
    EXPECT_FALSE(viewItem.setData(new_data, Qt::EditRole));
    EXPECT_EQ(viewItem.data(Qt::EditRole), new_data); // new data
}

//! ViewDataItem::data method for QColor.
//! Checks that the data method is correctly forwarded to underlying SessionItem.

TEST_F(RefViewItemsTest, ViewDataItem_dataForColor)
{
    // create SessionItem with data on board
    auto item = std::make_unique<SessionItem>();
    QVariant expected = QVariant::fromValue(QColor(Qt::green));
    EXPECT_TRUE(item->setData(expected));

    RefViewDataItem viewItem(item.get());
    EXPECT_EQ(viewItem.data(Qt::EditRole), expected);
    EXPECT_EQ(viewItem.data(Qt::DisplayRole), expected);
    EXPECT_EQ(viewItem.data(Qt::DecorationRole), expected);
}

//! ViewDataItem::setData for QColor.
//! Checks that the setData method is correctly forwarded to underlying SessionItem.

TEST_F(RefViewItemsTest, ViewDataItem_setDataForColor)
{
    // create SessionItem with data on board
    auto item = std::make_unique<SessionItem>();
    QVariant expected = QVariant::fromValue(QColor(Qt::green));
    EXPECT_TRUE(item->setData(expected));

    // initialize viewItem with sessionItem and set the data
    RefViewDataItem viewItem(item.get());
    QVariant new_data = QVariant::fromValue(QColor(Qt::red));
    EXPECT_TRUE(viewItem.setData(new_data, Qt::EditRole));
    EXPECT_EQ(viewItem.data(Qt::DisplayRole), new_data);    // new data
    EXPECT_EQ(viewItem.data(Qt::EditRole), new_data);       // new data
    EXPECT_EQ(viewItem.data(Qt::DecorationRole), new_data); // new data

    // SessionItem itself should have new data
    EXPECT_EQ(item->data(), new_data); // new data

    // it is not allowed to set another type of data to ViewDataItem
    QVariant not_allowed_value("Layer");
    EXPECT_THROW(viewItem.setData(not_allowed_value, Qt::EditRole), std::runtime_error);
}

//! Testing ViewLabelItem::flags.

TEST_F(RefViewItemsTest, ViewDataItem_flags)
{
    SessionItem item;
    QVariant expected = QVariant::fromValue(std::string("Layer"));
    EXPECT_TRUE(item.setData(expected, ItemDataRole::DATA));

    RefViewDataItem viewItem(&item);
    EXPECT_TRUE(viewItem.flags() & Qt::ItemIsEditable);
}
