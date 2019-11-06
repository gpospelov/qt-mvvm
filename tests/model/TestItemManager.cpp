#include "google_test.h"
#include <mvvm/model/itemmanager.h>
#include <mvvm/model/itempool.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <memory>

using namespace ModelView;

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
