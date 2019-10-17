#include "compounditem.h"
#include "google_test.h"
#include "itemfactory.h"
#include "jsonitemcopystrategy.h"
#include "propertyitem.h"
#include "standarditemcatalogue.h"

using namespace ModelView;

class TestJsonItemCopyStrategy : public ::testing::Test
{
public:
    TestJsonItemCopyStrategy()
        : m_factory(std::make_unique<ItemFactory>(CreateStandardItemCatalogue()))
    {
    }
    ~TestJsonItemCopyStrategy();

    std::unique_ptr<JsonItemCopyStrategy> createCopyStrategy()
    {
        return std::make_unique<JsonItemCopyStrategy>(m_factory.get());
    }

    std::unique_ptr<ItemFactory> m_factory;
};

TestJsonItemCopyStrategy::~TestJsonItemCopyStrategy() = default;

//! Saving/restoring PropertyItem.

TEST_F(TestJsonItemCopyStrategy, propertyItem)
{
    auto strategy = createCopyStrategy();

    PropertyItem item;
    item.setData(42.0);

    auto copy = strategy->createCopy(&item);

    EXPECT_EQ(item.modelType(), copy->modelType());
    EXPECT_EQ(item.data(), copy->data());
    EXPECT_FALSE(item.identifier() == copy->identifier());
}

//! Saving/restoring CompoundItem.

TEST_F(TestJsonItemCopyStrategy, compoundItem)
{
    auto strategy = createCopyStrategy();

    CompoundItem item;
    auto property = item.addProperty("thickness", 42.0);

    auto copy = strategy->createCopy(&item);

    EXPECT_EQ(item.modelType(), copy->modelType());
    EXPECT_EQ(copy->getItem("thickness")->data(), property->data());
    EXPECT_FALSE(copy->getItem("thickness")->identifier() == property->identifier());
    EXPECT_FALSE(item.identifier() == copy->identifier());
}

//! Saving/restoring CustomItem.

TEST_F(TestJsonItemCopyStrategy, customItem)
{
    auto strategy = createCopyStrategy();

    const std::string model_type(Constants::BaseType);

    // creating parent with one child
    auto parent = std::make_unique<SessionItem>(model_type);
    parent->setDisplayName("parent_name");
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);
    auto child = new SessionItem(model_type);
    child->setDisplayName("child_name");
    parent->insertItem(child, TagRow::append());

    // creating copy
    auto parent_copy = strategy->createCopy(parent.get());

    EXPECT_EQ(parent_copy->childrenCount(), 1);
    EXPECT_EQ(parent_copy->modelType(), model_type);
    EXPECT_EQ(parent_copy->displayName(), "parent_name");
    EXPECT_EQ(parent_copy->defaultTag(), "defaultTag");
    EXPECT_EQ(parent_copy->model(), nullptr);
    EXPECT_FALSE(parent_copy->identifier() == parent->identifier());

    // checking child reconstruction
    auto child_copy = parent_copy->getItem("defaultTag");
    EXPECT_EQ(child_copy->parent(), parent_copy.get());
    EXPECT_EQ(child_copy->childrenCount(), 0);
    EXPECT_EQ(child_copy->modelType(), model_type);
    EXPECT_EQ(child_copy->displayName(), "child_name");
    EXPECT_EQ(child_copy->defaultTag(), "");
    EXPECT_FALSE(child_copy->identifier() == child->identifier());
}
