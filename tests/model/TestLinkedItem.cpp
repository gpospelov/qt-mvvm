#include "MockWidgets.h"
#include "google_test.h"
#include "itempool.h"
#include "linkeditem.h"
#include "propertyitem.h"
#include "sessionmodel.h"

using namespace ModelView;
using ::testing::_;

//! LinkedItem tests.

class TestLinkedItem : public ::testing::Test
{
public:
    ~TestLinkedItem();
};

TestLinkedItem::~TestLinkedItem() = default;

//! Initial state of item when it is created outside of model context.

TEST_F(TestLinkedItem, initialState)
{
    LinkedItem item;
    EXPECT_EQ(item.get(), nullptr);
}

//! Link in single model context.

TEST_F(TestLinkedItem, sameModelContext)
{
    SessionModel model;
    auto item = model.insertItem<PropertyItem>();
    auto link = model.insertItem<LinkedItem>();

    // no link by default
    EXPECT_EQ(link->get(), nullptr);

    // setting the link
    link->setLink(item);

    // now linked
    EXPECT_EQ(link->get(), item);
    EXPECT_EQ(link->data().value<std::string>(), item->identifier());
}

//! Link in different model context.

TEST_F(TestLinkedItem, differentModelContext)
{
    auto pool = std::make_shared<ItemPool>();

    SessionModel model1("TestModel1", pool);
    SessionModel model2("TestModel2", pool);

    auto item = model1.insertItem<PropertyItem>();
    auto link = model2.insertItem<LinkedItem>();

    // no link by default
    EXPECT_EQ(link->get(), nullptr);

    // setting the link
    link->setLink(item);

    // now linked
    EXPECT_EQ(link->get(), item);
}

//! Signals when links is set.

TEST_F(TestLinkedItem, onSetLink)
{
    SessionModel model;
    auto item = model.insertItem<PropertyItem>();
    auto link = model.insertItem<LinkedItem>();

    // no link by default
    EXPECT_EQ(link->get(), nullptr);

    MockWidgetForItem widget(link);

    auto expected_role = ItemDataRole::DATA;
    auto expected_item = link;
    EXPECT_CALL(widget, onDataChange(expected_item, expected_role)).Times(1);
    EXPECT_CALL(widget, onPropertyChange(_, _)).Times(0);

    // making action
    link->setLink(item);
}

//! Link in different model context.

TEST_F(TestLinkedItem, setNullAsLink)
{
    auto pool = std::make_shared<ItemPool>();

    SessionModel model("TestModel", pool);
    auto link = model.insertItem<LinkedItem>();
    auto item = model.insertItem<PropertyItem>();

    // no link by default
    EXPECT_EQ(link->get(), nullptr);

    // setting link
    link->setLink(item);
    EXPECT_EQ(link->get(), item);

    // still null link
    link->setLink(nullptr);
    EXPECT_EQ(link->get(), nullptr);
    EXPECT_FALSE(link->data().isValid());
}
