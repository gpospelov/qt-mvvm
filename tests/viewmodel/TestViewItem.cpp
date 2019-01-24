#include "google_test.h"
#include "viewitem.h"
#include "sessionitem.h"
#include <memory>

using namespace ModelView;

class TestViewItem : public ::testing::Test
{
public:
    ~TestViewItem();
};

TestViewItem::~TestViewItem() = default;

TEST_F(TestViewItem, initialState)
{
    std::unique_ptr<SessionItem> item(new SessionItem);

    ViewItem viewItem(item.get());
    EXPECT_EQ(viewItem.item(), item.get());
}

//! Checks that the data method is correctly forwarded to underlying SessionItem.

TEST_F(TestViewItem, data)
{
    // create SessionItem with data on board
    std::unique_ptr<SessionItem> item(new SessionItem);
    QVariant expected(42.0);
    EXPECT_TRUE(item->setData(expected, ItemDataRole::DATA));

    // initialize viewItem with sessionItem and check the data
    ViewItem viewItem(item.get());
    EXPECT_EQ(viewItem.data(Qt::DisplayRole), expected);
    EXPECT_EQ(viewItem.data(Qt::EditRole), expected);
}

//! Checks that the setData method is correctly forwarded to underlying SessionItem.

TEST_F(TestViewItem, setData)
{
    // create SessionItem with data on board
    std::unique_ptr<SessionItem> item(new SessionItem);
    QVariant expected(42.0);
    EXPECT_TRUE(item->setData(expected, ItemDataRole::DATA));

    // initialize viewItem with sessionItem and set the data
    ViewItem viewItem(item.get());
    QVariant new_data(43.0);
    viewItem.setData(new_data, Qt::EditRole);
    EXPECT_EQ(viewItem.data(Qt::DisplayRole), new_data); // new data
    EXPECT_EQ(viewItem.data(Qt::EditRole), new_data); // new data

    // SessionItem itself should have new data
    EXPECT_EQ(item->data(ItemDataRole::DATA), new_data); // new data
}



