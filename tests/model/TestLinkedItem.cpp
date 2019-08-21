#include "google_test.h"
#include "linkeditem.h"
#include "sessionmodel.h"
#include "itempool.h"

using namespace ModelView;

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
