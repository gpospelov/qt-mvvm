#include <gtest/gtest.h>
#include "itempool.h"
#include "sessionitem.h"
#include <memory>

class TestItemPool : public ::testing::Test
{
public:
    ~TestItemPool();
};

TestItemPool::~TestItemPool() = default;

TEST_F(TestItemPool, initialState)
{
    std::unique_ptr<ItemPool> pool(new ItemPool);
    EXPECT_EQ(pool->size(), 0u);
}

TEST_F(TestItemPool, registerItem)
{
    std::unique_ptr<ItemPool> pool(new ItemPool);
    std::unique_ptr<SessionItem> item(new SessionItem);

    // registering item
    auto key = pool->register_item(item.get());
    EXPECT_EQ(pool->size(), 1u);
    EXPECT_FALSE(key.empty());

    // checking registered key and item
    EXPECT_EQ(key, pool->key_for_item(item.get()));
    EXPECT_EQ(item.get(), pool->item_for_key(key));

    // checking unexisting registration
    std::unique_ptr<SessionItem> item2(new SessionItem);
    EXPECT_EQ(ItemPool::key_type(), pool->key_for_item(item2.get()));
    EXPECT_EQ(nullptr, pool->item_for_key("ABC"));

    // registering second item
    auto key2 = pool->register_item(item2.get());
    EXPECT_EQ(pool->size(), 2u);
    EXPECT_EQ(key2, pool->key_for_item(item2.get()));
    EXPECT_FALSE(key == key2);

    // attempt to register item twice
    EXPECT_THROW(pool->register_item(item2.get()), std::runtime_error);
}

TEST_F(TestItemPool, deregisterItem)
{
    std::unique_ptr<ItemPool> pool(new ItemPool);
    std::unique_ptr<SessionItem> item1(new SessionItem);
    std::unique_ptr<SessionItem> item2(new SessionItem);

    auto key1 = pool->register_item(item1.get());
    auto key2 = pool->register_item(item2.get());

    EXPECT_EQ(pool->size(), 2u);
    EXPECT_EQ(item1.get(), pool->item_for_key(key1));
    EXPECT_EQ(item2.get(), pool->item_for_key(key2));

    // deregistering item
    pool->deregister_item(item1.get());
    EXPECT_EQ(pool->size(), 1u);
    EXPECT_EQ(nullptr, pool->item_for_key(key1));
    EXPECT_EQ(item2.get(), pool->item_for_key(key2));

    // attempt to deregister twice
    EXPECT_THROW(pool->deregister_item(item1.get()), std::runtime_error);

    // deregistering last remaining item
    pool->deregister_item(item2.get());
    EXPECT_EQ(pool->size(), 0u);
}


