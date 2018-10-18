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
    ItemManager manager;
    EXPECT_EQ(manager.itemPool(), nullptr);

    std::shared_ptr<ItemPool> pool(new ItemPool);
    manager.setItemPool(pool);
    EXPECT_EQ(manager.itemPool(), pool.get());
    EXPECT_EQ(manager.itemPool()->size(), 0);
}

//! Creation of item through factory leads to the item registration in a pool.

TEST_F(TestItemManager, createItem)
{
    ItemManager manager;
    std::shared_ptr<ItemPool> pool(new ItemPool);
    manager.setItemPool(pool);

    std::unique_ptr<SessionItem> item(manager.createRootItem());

    EXPECT_EQ(manager.itemPool()->size(), 1u);

    auto id = manager.findIdentifier(item.get());
    EXPECT_EQ(manager.findItem(id), item.get());

    // item deletion leads to its automatic deregistration
    item.reset();
    EXPECT_EQ(manager.findItem(id), nullptr);
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

