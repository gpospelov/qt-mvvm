// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/serialization/jsonitembackupstrategy.h"

#include "google_test.h"
#include "mvvm/factories/itemcataloguefactory.h"
#include "mvvm/model/compounditem.h"
#include "mvvm/model/itemfactory.h"
#include "mvvm/model/propertyitem.h"
#include "mvvm/model/sessionitemtags.h"

using namespace ModelView;

class JsonItemBackupStrategyTest : public ::testing::Test {
public:
    JsonItemBackupStrategyTest()
        : m_factory(std::make_unique<ItemFactory>(CreateStandardItemCatalogue()))
    {
    }

    std::unique_ptr<JsonItemBackupStrategy> createBackupStrategy()
    {
        return std::make_unique<JsonItemBackupStrategy>(m_factory.get());
    }

    std::unique_ptr<ItemFactory> m_factory;
};

//! Saving/restoring PropertyItem.

TEST_F(JsonItemBackupStrategyTest, propertyItem)
{
    auto strategy = createBackupStrategy();

    PropertyItem item;
    item.setData(42.0);

    strategy->saveItem(&item);
    auto restored = strategy->restoreItem();

    EXPECT_EQ(item.modelType(), restored->modelType());
    EXPECT_EQ(item.identifier(), restored->identifier());
    EXPECT_EQ(item.data<QVariant>(), restored->data<QVariant>());
}

//! Saving/restoring CompoundItem.

TEST_F(JsonItemBackupStrategyTest, compoundItem)
{
    auto strategy = createBackupStrategy();

    CompoundItem item;
    auto property = item.addProperty("thickness", 42.0);

    strategy->saveItem(&item);
    auto restored = strategy->restoreItem();

    EXPECT_EQ(item.modelType(), restored->modelType());
    EXPECT_EQ(item.identifier(), restored->identifier());
    EXPECT_EQ(restored->getItem("thickness")->data<double>(), property->data<double>());
    EXPECT_EQ(restored->getItem("thickness")->identifier(), property->identifier());
}

//! Saving/restoring CustomItem.

TEST_F(JsonItemBackupStrategyTest, customItem)
{
    auto strategy = createBackupStrategy();

    const std::string model_type(Constants::BaseType);

    // creating parent with one child
    auto parent = std::make_unique<SessionItem>(model_type);
    parent->setDisplayName("parent_name");
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);

    auto child = parent->insertItem(std::make_unique<SessionItem>(model_type), TagRow::append());
    child->setDisplayName("child_name");

    // creating copy
    strategy->saveItem(parent.get());
    auto reco_parent = strategy->restoreItem();

    EXPECT_EQ(reco_parent->childrenCount(), 1);
    EXPECT_EQ(reco_parent->modelType(), model_type);
    EXPECT_EQ(reco_parent->displayName(), "parent_name");
    EXPECT_EQ(reco_parent->identifier(), parent->identifier());
    EXPECT_EQ(reco_parent->itemTags()->defaultTag(), "defaultTag");
    EXPECT_EQ(reco_parent->model(), nullptr);

    // checking child reconstruction
    auto reco_child = reco_parent->getItem("defaultTag");
    EXPECT_EQ(reco_child->parent(), reco_parent.get());
    EXPECT_EQ(reco_child->childrenCount(), 0);
    EXPECT_EQ(reco_child->modelType(), model_type);
    EXPECT_EQ(reco_child->displayName(), "child_name");
    EXPECT_EQ(reco_child->identifier(), child->identifier());
    EXPECT_EQ(reco_child->itemTags()->defaultTag(), "");
}
