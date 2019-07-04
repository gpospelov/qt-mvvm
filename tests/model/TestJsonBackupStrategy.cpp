#include "compounditem.h"
#include "google_test.h"
#include "itemfactory.h"
#include "jsonbackupstrategy.h"
#include "propertyitem.h"
#include "standarditemcatalogue.h"

using namespace ModelView;

class TestJsonBackupStrategy : public ::testing::Test
{
public:
    TestJsonBackupStrategy()
        : m_factory(std::make_unique<ItemFactory>(CreateStandardItemCatalogue()))
    {
    }
    ~TestJsonBackupStrategy();

    std::unique_ptr<JsonBackupStrategy> createBackupStrategy()
    {
        return std::make_unique<JsonBackupStrategy>(m_factory.get());
    }

    std::unique_ptr<ItemFactory> m_factory;
};

TestJsonBackupStrategy::~TestJsonBackupStrategy() = default;

//! Saving/restoring PropertyItem.

TEST_F(TestJsonBackupStrategy, propertyItem)
{
    auto strategy = createBackupStrategy();

    PropertyItem item;
    item.setData(42.0, ItemDataRole::DATA);

    strategy->saveItem(&item);
    auto restored = strategy->restoreItem();

    EXPECT_EQ(item.modelType(), restored->modelType());
    EXPECT_EQ(item.identifier(), restored->identifier());
    EXPECT_EQ(item.data(ItemDataRole::DATA), restored->data(ItemDataRole::DATA));
}

//! Saving/restoring CompoundItem.

TEST_F(TestJsonBackupStrategy, compoundItem)
{
    auto strategy = createBackupStrategy();

    CompoundItem item;
    auto property = item.addProperty("thickness", 42.0);

    strategy->saveItem(&item);
    auto restored = strategy->restoreItem();

    EXPECT_EQ(item.modelType(), restored->modelType());
    EXPECT_EQ(item.identifier(), restored->identifier());
    EXPECT_EQ(restored->getItem("thickness")->data(ItemDataRole::DATA),
              property->data(ItemDataRole::DATA));
    EXPECT_EQ(restored->getItem("thickness")->identifier(), property->identifier());
}

//! Saving/restoring CustomItem.

TEST_F(TestJsonBackupStrategy, customItem)
{
    auto strategy = createBackupStrategy();

    const std::string model_type(Constants::BaseType);

    // creating parent with one child
    auto parent = std::make_unique<SessionItem>(model_type);
    parent->setDisplayName("parent_name");
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);
    auto child = new SessionItem(model_type);
    child->setDisplayName("child_name");
    parent->insertItem(child, "", -1);

    // creating copy
    strategy->saveItem(parent.get());
    auto reco_parent = strategy->restoreItem();

    EXPECT_EQ(reco_parent->childrenCount(), 1);
    EXPECT_EQ(reco_parent->modelType(), model_type);
    EXPECT_EQ(reco_parent->displayName(), "parent_name");
    EXPECT_EQ(reco_parent->identifier(), parent->identifier());
    EXPECT_EQ(reco_parent->defaultTag(), "defaultTag");
    EXPECT_EQ(reco_parent->model(), nullptr);

    // checking child reconstruction
    auto reco_child = reco_parent->getItem("defaultTag");
    EXPECT_EQ(reco_child->parent(), reco_parent.get());
    EXPECT_EQ(reco_child->childrenCount(), 0);
    EXPECT_EQ(reco_child->modelType(), model_type);
    EXPECT_EQ(reco_child->displayName(), "child_name");
    EXPECT_EQ(reco_child->identifier(), child->identifier());
    EXPECT_EQ(reco_child->defaultTag(), "");
}
