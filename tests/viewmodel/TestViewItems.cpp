#include "google_test.h"
#include "viewitems.h"
#include "sessionitem.h"
#include "toy_includes.h"
#include <memory>
#include <QDebug>

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

    ViewDataItem viewItem(item.get());
    EXPECT_EQ(viewItem.item(), item.get());
}

//! ViewDataItem::data method
//! Checks that the data method is correctly forwarded to underlying SessionItem.

TEST_F(TestViewItem, ViewDataItem_data)
{
    // create SessionItem with data on board
    std::unique_ptr<SessionItem> item(new SessionItem);
    QVariant expected(42.0);
    EXPECT_TRUE(item->setData(expected, ItemDataRole::DATA));

    // initialize viewItem with sessionItem and check the data
    ViewDataItem viewItem(item.get());
    EXPECT_EQ(viewItem.data(Qt::EditRole), expected);
    EXPECT_EQ(viewItem.data(Qt::DisplayRole), expected);
}

//! ViewLabelItem::data method
//! Checks that the data method is correctly forwarded to underlying SessionItem.

TEST_F(TestViewItem, ViewLabelItem_data)
{
    // create SessionItem with data on board
    std::unique_ptr<SessionItem> item(new SessionItem);
    QVariant expected = QVariant::fromValue(std::string("Layer"));
    EXPECT_TRUE(item->setData(expected, ItemDataRole::DISPLAY));

    // initialize viewItem with sessionItem and check the data
    ViewLabelItem viewItem(item.get());
    EXPECT_EQ(toCustomVariant(viewItem.data(Qt::EditRole)), expected);
    EXPECT_EQ(toCustomVariant(viewItem.data(Qt::DisplayRole)), expected);
}

//! ViewDataItem::setData
//! Checks that the setData method is correctly forwarded to underlying SessionItem.

TEST_F(TestViewItem, ViewDataItem_setData)
{
    // create SessionItem with data on board
    std::unique_ptr<SessionItem> item(new SessionItem);
    QVariant expected(42.0);
    EXPECT_TRUE(item->setData(expected, ItemDataRole::DATA));

    // initialize viewItem with sessionItem and set the data
    ViewDataItem viewItem(item.get());
    QVariant new_data(43.0);
    viewItem.setData(new_data, Qt::EditRole);
    EXPECT_EQ(viewItem.data(Qt::DisplayRole), new_data); // new data
    EXPECT_EQ(viewItem.data(Qt::EditRole), new_data); // new data

    // SessionItem itself should have new data
    EXPECT_EQ(item->data(ItemDataRole::DATA), new_data); // new data

    // it is not allowed to set another type of data to ViewDataItem
    QVariant not_allowed_value("Layer");
    EXPECT_THROW(viewItem.setData(not_allowed_value, Qt::EditRole), std::runtime_error);
}

//! ViewLabelItem::setData
//! Checks that the setData method is correctly forwarded to underlying SessionItem.

TEST_F(TestViewItem, ViewLabelItem_setData)
{
    // create SessionItem with data on board
    std::unique_ptr<SessionItem> item(new SessionItem);
    QVariant expected = QVariant::fromValue(std::string("Layer"));
    EXPECT_TRUE(item->setData(expected, ItemDataRole::DISPLAY));

    // initialize viewItem with sessionItem and set the data
    ViewLabelItem viewItem(item.get());
    QVariant new_data("MultiLayer");
    viewItem.setData(new_data, Qt::EditRole);
    EXPECT_EQ(viewItem.data(Qt::DisplayRole), new_data); // new data
    EXPECT_EQ(viewItem.data(Qt::EditRole), new_data); // new data

    // SessionItem itself should have new data
    EXPECT_EQ(item->data(ItemDataRole::DISPLAY), toCustomVariant(new_data)); // new data

    // it is not allowed to set another type of data to ViewLabelItem
    QVariant not_allowed_value(42);
    EXPECT_THROW(viewItem.setData(not_allowed_value, Qt::EditRole), std::runtime_error);
}

//! How ViewLabelItem sees MultiLayer

TEST_F(TestViewItem, viewItemsForMultiLayer)
{
    ToyItems::SampleModel model;

    auto multiLayer = model.insertNewItem(ToyItems::Constants::MultiLayerType);

    ViewLabelItem labelItem(multiLayer);
    EXPECT_EQ(labelItem.data(Qt::DisplayRole).toString().toStdString(), ToyItems::Constants::MultiLayerType);
}

