#include <gtest/gtest.h>
#include "itemfactory.h"
#include "itempool.h"
#include "sessionmodel.h"
#include "sessionitem.h"
#include <memory>

//! Testing ItemFactory in the context of SessionModel and unique identifiers of SessionItem.

class TestItemFactory : public ::testing::Test
{
public:
    ~TestItemFactory();
};

TestItemFactory::~TestItemFactory() = default;

TEST_F(TestItemFactory, initialState)
{
    ItemFactory factory;
    EXPECT_EQ(factory.itemPool().size(), 0u);
}

TEST_F(TestItemFactory, createItem)
{
    ItemFactory factory;
    std::unique_ptr<SessionItem> item(factory.createEmptyItem());

    EXPECT_EQ(factory.itemPool().size(), 1u);

    auto id = factory.findIdentifier(item.get());
    EXPECT_EQ(factory.findItem(id), item.get());

    factory.forgetItem(item.get());
    EXPECT_EQ(factory.findItem(id), nullptr);
}

//! Checking that in the model context the deletion of item will lead to
//! id dissapearance.

TEST_F(TestItemFactory, modelContext)
{
    SessionModel model;
    auto factory = model.factory();

    EXPECT_EQ(factory->itemPool().size(), 1u); // root item already there

    auto item1 = model.insertNewItem("abc");
    EXPECT_EQ(factory->itemPool().size(), 2u);
    auto key = factory->findIdentifier(item1);
    EXPECT_EQ(factory->findItem(key), item1);

    delete item1;
    EXPECT_EQ(factory->itemPool().size(), 1u);
    EXPECT_EQ(factory->findItem(key), nullptr);
}
