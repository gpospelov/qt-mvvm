#include <gtest/gtest.h>
#include "itemmanager.h"
#include "itempool.h"
#include "sessionmodel.h"
#include "sessionitem.h"
#include <memory>

//! Testing ItemFactory in the context of SessionModel and unique identifiers of SessionItem.

class TestItemManager : public ::testing::Test
{
public:
    ~TestItemManager();
};

TestItemManager::~TestItemManager() = default;

TEST_F(TestItemManager, initialState)
{
    ItemManager factory;
    EXPECT_EQ(factory.itemPool()->size(), 0u);
}

//! Creation of item through factory leads to the item registration in a pool.

TEST_F(TestItemManager, createItem)
{
    ItemManager factory;
    std::unique_ptr<SessionItem> item(factory.createRootItem());

    EXPECT_EQ(factory.itemPool()->size(), 1u);

    auto id = factory.findIdentifier(item.get());
    EXPECT_EQ(factory.findItem(id), item.get());

    // item deletion leads to its automatic deregistration
    item.reset();
    EXPECT_EQ(factory.findItem(id), nullptr);
}


//! Item factory should forget the item on item deletion (in the model context).

TEST_F(TestItemManager, modelContext)
{
    SessionModel model;
    auto manager = model.manager();

    EXPECT_EQ(manager->itemPool()->size(), 1u); // root item already there

    auto item1 = model.insertNewItem("abc");
    EXPECT_EQ(manager->itemPool()->size(), 2u);
    auto key = manager->findIdentifier(item1);
    EXPECT_EQ(manager->findItem(key), item1);

    delete item1;
    EXPECT_EQ(manager->itemPool()->size(), 1u);
    EXPECT_EQ(manager->findItem(key), nullptr);
}

