#include "google_test.h"
#include "itemcatalogue.h"
#include "propertyitem.h"
#include "vectoritem.h"
#include "defaultitemcatalogue.h"

using namespace ModelView;

//! Testing ItemCatalogue construction

class TestItemCatalogue : public ::testing::Test
{
public:
    ~TestItemCatalogue();
};

TestItemCatalogue::~TestItemCatalogue() = default;


TEST_F(TestItemCatalogue, addItem)
{
    ItemCatalogue catalogue;

    catalogue.add<PropertyItem>();

    auto item = catalogue.create(Constants::PropertyType);
    EXPECT_TRUE(dynamic_cast<PropertyItem*>(item.get()) != nullptr);

    // registration of second item is not allowed
    EXPECT_THROW(catalogue.add<PropertyItem>(), std::runtime_error);

    // item was not registered, creation not allowed
    EXPECT_THROW(catalogue.create("non-registered"), std::runtime_error);
}

TEST_F(TestItemCatalogue, copyConstructor)
{
    ItemCatalogue catalogue;
    catalogue.add<PropertyItem>();

    ItemCatalogue copy(catalogue);

    // creation of item using first catalogue
    auto item = catalogue.create(Constants::PropertyType);
    EXPECT_TRUE(dynamic_cast<PropertyItem*>(item.get()) != nullptr);

    // creation of item using catalogue copy
    item = copy.create(Constants::PropertyType);
    EXPECT_TRUE(dynamic_cast<PropertyItem*>(item.get()) != nullptr);

    // adding item to first catalogue but not the second
    catalogue.add<VectorItem>();
    item = catalogue.create(Constants::VectorType);
    EXPECT_TRUE(dynamic_cast<VectorItem*>(item.get()) != nullptr);

    // copy of catalogue knows nothing about new VectorType
    EXPECT_THROW(copy.create(Constants::VectorType), std::runtime_error);
}

TEST_F(TestItemCatalogue, assignmentOperator)
{
    ItemCatalogue catalogue;
    catalogue.add<PropertyItem>();

    ItemCatalogue copy;
    copy = catalogue;

    // creation of item using first catalogue
    auto item = catalogue.create(Constants::PropertyType);
    EXPECT_TRUE(dynamic_cast<PropertyItem*>(item.get()) != nullptr);

    // creation of item using catalogue copy
    item = copy.create(Constants::PropertyType);
    EXPECT_TRUE(dynamic_cast<PropertyItem*>(item.get()) != nullptr);
}

TEST_F(TestItemCatalogue, defaultItemCatalogue)
{
    ItemCatalogue catalogue = CreateDefaultItemCatalogue();

    auto item = catalogue.create(Constants::SessionItemType);
    EXPECT_TRUE(dynamic_cast<SessionItem*>(item.get()) != nullptr);

    item = catalogue.create(Constants::PropertyType);
    EXPECT_TRUE(dynamic_cast<PropertyItem*>(item.get()) != nullptr);

    item = catalogue.create(Constants::VectorType);
    EXPECT_TRUE(dynamic_cast<VectorItem*>(item.get()) != nullptr);

    item = catalogue.create(Constants::CompoundType);
    EXPECT_TRUE(dynamic_cast<CompoundItem*>(item.get()) != nullptr);
}
