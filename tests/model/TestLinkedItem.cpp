#include "google_test.h"
#include "linkeditem.h"
#include "sessionmodel.h"
#include "itempool.h"
#include "MockWidgets.h"

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
    EXPECT_EQ(item.linkedItem(), nullptr);
}

//! Link in single model context.

TEST_F(TestLinkedItem, sameModelContext)
{
    SessionModel model;
    auto item = model.insertNewItem(Constants::PropertyType);
    auto linked = dynamic_cast<LinkedItem*>(model.insertNewItem(Constants::LinkedType));

    // no link by default
    EXPECT_EQ(linked->linkedItem(), nullptr);

    // setting the link
    linked->setLink(item);

    // now linked
    EXPECT_EQ(linked->linkedItem(), item);
    EXPECT_EQ(linked->data().value<std::string>(), item->identifier());
}

//! Link in different model context.

TEST_F(TestLinkedItem, differentModelContext)
{
    auto pool = std::make_shared<ItemPool>();

    SessionModel model1("TestModel1", pool);
    SessionModel model2("TestModel2", pool);

    auto item = model1.insertNewItem(Constants::PropertyType);
    auto linked = dynamic_cast<LinkedItem*>(model2.insertNewItem(Constants::LinkedType));

    // no link by default
    EXPECT_EQ(linked->linkedItem(), nullptr);

    // setting the link
    linked->setLink(item);

    // now linked
    EXPECT_EQ(linked->linkedItem(), item);
}

//! Signals when links is set.

TEST_F(TestLinkedItem, onSetLink)
{
    SessionModel model;
    auto item = model.insertNewItem(Constants::PropertyType);
    auto linked = dynamic_cast<LinkedItem*>(model.insertNewItem(Constants::LinkedType));

    // no link by default
    EXPECT_EQ(linked->linkedItem(), nullptr);

    MockWidgetForItem widget(linked);

    auto expected_role = ItemDataRole::DATA;
    auto expected_item = linked;
    EXPECT_CALL(widget, onDataChange(expected_item, expected_role)).Times(1);
    EXPECT_CALL(widget, onPropertyChange(_, _)).Times(0);

    // making action
    linked->setLink(item);
}

//! Link in different model context.

TEST_F(TestLinkedItem, setNullAsLink)
{
    auto pool = std::make_shared<ItemPool>();

    SessionModel model("TestModel", pool);
    auto linked = dynamic_cast<LinkedItem*>(model.insertNewItem(Constants::LinkedType));
    auto item = model.insertNewItem(Constants::PropertyType);

    // no link by default
    EXPECT_EQ(linked->linkedItem(), nullptr);

    // setting link
    linked->setLink(item);
    EXPECT_EQ(linked->linkedItem(), item);

    // still null link
    linked->setLink(nullptr);
    EXPECT_EQ(linked->linkedItem(), nullptr);
    EXPECT_FALSE(linked->data().isValid());
}
