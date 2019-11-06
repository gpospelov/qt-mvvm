// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <QDebug>
#include <memory>
#include <mvvm/model/sessionitem.h>
#include <mvvm/viewmodel/viewdataitem.h>

using namespace ModelView;

class ViewDataItemTest : public ::testing::Test
{
public:
    ~ViewDataItemTest();
};

ViewDataItemTest::~ViewDataItemTest() = default;

TEST_F(ViewDataItemTest, initialState)
{
    std::unique_ptr<SessionItem> item(new SessionItem);

    ViewDataItem viewItem(item.get());
    EXPECT_EQ(viewItem.item(), item.get());
    EXPECT_EQ(viewItem.item_role(), ItemDataRole::DATA);
}

//! ViewDataItem::data method for double values.
//! Checks that the data method is correctly forwarded to underlying SessionItem.

TEST_F(ViewDataItemTest, dataForDouble)
{
    // create SessionItem with data on board
    auto item = std::make_unique<SessionItem>();
    QVariant expected(42.0);
    EXPECT_TRUE(item->setData(expected));

    // initialize viewItem with sessionItem and check the data
    ViewDataItem viewItem(item.get());
    EXPECT_EQ(viewItem.data(Qt::EditRole), expected);
    EXPECT_EQ(viewItem.data(Qt::DisplayRole), expected);
}

//! ViewDataItem::setData for double values.
//! Checks that the setData method is correctly forwarded to underlying SessionItem.

TEST_F(ViewDataItemTest, setDataForDouble)
{
    // create SessionItem with data on board
    auto item = std::make_unique<SessionItem>();
    QVariant expected(42.0);
    EXPECT_TRUE(item->setData(expected));

    // initialize viewItem with sessionItem and set the data
    ViewDataItem viewItem(item.get());
    QVariant new_data(43.0);
    viewItem.setData(new_data, Qt::EditRole);
    EXPECT_EQ(viewItem.data(Qt::DisplayRole), new_data); // new data
    EXPECT_EQ(viewItem.data(Qt::EditRole), new_data);    // new data

    // SessionItem itself should have new data
    EXPECT_EQ(item->data(), new_data); // new data

    // it is not allowed to set another type of data to ViewDataItem
    QVariant not_allowed_value("Layer");
    EXPECT_THROW(viewItem.setData(not_allowed_value, Qt::EditRole), std::runtime_error);
}

//! ViewDataItem::data method for QColor.
//! Checks that the data method is correctly forwarded to underlying SessionItem.

TEST_F(ViewDataItemTest, dataForColor)
{
    // create SessionItem with data on board
    auto item = std::make_unique<SessionItem>();
    QVariant expected = QVariant::fromValue(QColor(Qt::green));
    EXPECT_TRUE(item->setData(expected));

    ViewDataItem viewItem(item.get());
    EXPECT_EQ(viewItem.data(Qt::EditRole), expected);
    EXPECT_EQ(viewItem.data(Qt::DisplayRole), expected);
    EXPECT_EQ(viewItem.data(Qt::DecorationRole), expected);
}

//! ViewDataItem::setData for QColor.
//! Checks that the setData method is correctly forwarded to underlying SessionItem.

TEST_F(ViewDataItemTest, setDataForColor)
{
    // create SessionItem with data on board
    auto item = std::make_unique<SessionItem>();
    QVariant expected = QVariant::fromValue(QColor(Qt::green));
    EXPECT_TRUE(item->setData(expected));

    // initialize viewItem with sessionItem and set the data
    ViewDataItem viewItem(item.get());
    QVariant new_data = QVariant::fromValue(QColor(Qt::red));
    viewItem.setData(new_data, Qt::EditRole);
    EXPECT_EQ(viewItem.data(Qt::DisplayRole), new_data);    // new data
    EXPECT_EQ(viewItem.data(Qt::EditRole), new_data);       // new data
    EXPECT_EQ(viewItem.data(Qt::DecorationRole), new_data); // new data

    // SessionItem itself should have new data
    EXPECT_EQ(item->data(), new_data); // new data

    // it is not allowed to set another type of data to ViewDataItem
    QVariant not_allowed_value("Layer");
    EXPECT_THROW(viewItem.setData(not_allowed_value, Qt::EditRole), std::runtime_error);
}
