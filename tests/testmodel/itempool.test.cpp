// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <memory>
#include <mvvm/model/itempool.h>
#include <mvvm/model/sessionitem.h>
#include <stdexcept>

using namespace ModelView;

//! Tests of ItemPool and its abilities to register/deregister SessionItem.

class ItemPoolTest : public ::testing::Test
{
public:
    ~ItemPoolTest();
};

ItemPoolTest::~ItemPoolTest() = default;

TEST_F(ItemPoolTest, initialState)
{
    std::unique_ptr<ItemPool> pool(new ItemPool);
    EXPECT_EQ(pool->size(), 0u);
}

//! Explicit item registrations.

TEST_F(ItemPoolTest, registerItem)
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
    EXPECT_EQ(identifier_type(), pool->key_for_item(item2.get()));
    EXPECT_EQ(nullptr, pool->item_for_key("ABC"));

    // registering second item
    auto key2 = pool->register_item(item2.get());
    EXPECT_EQ(pool->size(), 2u);
    EXPECT_EQ(key2, pool->key_for_item(item2.get()));
    EXPECT_FALSE(key == key2);

    // attempt to register item twice
    EXPECT_THROW(pool->register_item(item2.get()), std::runtime_error);
}

//! Explicit item de-registrations.

TEST_F(ItemPoolTest, deregisterItem)
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
    pool->unregister_item(item1.get());
    EXPECT_EQ(pool->size(), 1u);
    EXPECT_EQ(nullptr, pool->item_for_key(key1));
    EXPECT_EQ(item2.get(), pool->item_for_key(key2));

    // attempt to deregister twice
    EXPECT_THROW(pool->unregister_item(item1.get()), std::runtime_error);

    // deregistering last remaining item
    pool->unregister_item(item2.get());
    EXPECT_EQ(pool->size(), 0u);
}

//! Providing custom key.

TEST_F(ItemPoolTest, customKey)
{
    std::shared_ptr<ItemPool> pool(new ItemPool);
    EXPECT_EQ(pool.use_count(), 1l);

    // explicit item registration
    const identifier_type id("abc-cde-fgh");
    auto item = new SessionItem;
    pool->register_item(item, id);

    // attempt to reuse key again
    std::unique_ptr<SessionItem> item2(new SessionItem);
    EXPECT_THROW(pool->register_item(item2.get(), id), std::runtime_error);

    delete item;
}
