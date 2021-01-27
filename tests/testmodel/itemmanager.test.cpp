// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/model/itemmanager.h"

#include "google_test.h"
#include "mvvm/model/itempool.h"
#include <memory>

using namespace ModelView;

//! Testing ItemFactory in the context of SessionModel and unique identifiers of SessionItem.

class ItemManagerTest : public ::testing::Test {
};

TEST_F(ItemManagerTest, initialState)
{
    ItemManager manager;
    EXPECT_EQ(manager.itemPool(), nullptr);

    std::shared_ptr<ItemPool> pool(new ItemPool);
    manager.setItemPool(pool);
    EXPECT_EQ(manager.itemPool(), pool.get());
    EXPECT_EQ(manager.itemPool()->size(), 0);
}
