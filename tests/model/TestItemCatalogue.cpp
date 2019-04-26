#include "google_test.h"
#include "itemcatalogue.h"
#include "propertyitem.h"
#include "vectoritem.h"
#include "standarditemcatalogue.h"

using namespace ModelView;

//! Testing ItemCatalogue construction

class TestItemCatalogue : public ::testing::Test
{
public:
    ~TestItemCatalogue();
};

TestItemCatalogue::~TestItemCatalogue() = default;

TEST_F(TestItemCatalogue, initialState)
{
    ItemCatalogue catalogue;
    EXPECT_EQ(catalogue.itemCount(), 0);
    EXPECT_EQ(catalogue.modelTypes(), std::vector<std::string>({}));
    EXPECT_EQ(catalogue.labels(), std::vector<std::string>({}));
}

TEST_F(TestItemCatalogue, addItem)
{
    ItemCatalogue catalogue;

    catalogue.add<PropertyItem>();

    EXPECT_EQ(catalogue.itemCount(), 1);

    auto item = catalogue.create(Constants::PropertyType);
    EXPECT_TRUE(dynamic_cast<PropertyItem*>(item.get()) != nullptr);

    // registration of second item is not allowed
    EXPECT_THROW(catalogue.add<PropertyItem>(), std::runtime_error);

    // item was not registered, creation not allowed
    EXPECT_THROW(catalogue.create("non-registered"), std::runtime_error);

    // checking model types and labels
    EXPECT_EQ(catalogue.modelTypes(), std::vector<std::string>({"Property"}));
    EXPECT_EQ(catalogue.labels(), std::vector<std::string>({""}));
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

    // checking model types and labels in new catalogue
    EXPECT_EQ(copy.modelTypes(), std::vector<std::string>({"Property"}));
    EXPECT_EQ(copy.labels(), std::vector<std::string>({""}));

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
    auto catalogue = CreateStandardItemCatalogue();

    auto item = catalogue->create(Constants::BaseType);
    EXPECT_TRUE(dynamic_cast<SessionItem*>(item.get()) != nullptr);

    item = catalogue->create(Constants::PropertyType);
    EXPECT_TRUE(dynamic_cast<PropertyItem*>(item.get()) != nullptr);

    item = catalogue->create(Constants::VectorType);
    EXPECT_TRUE(dynamic_cast<VectorItem*>(item.get()) != nullptr);

    item = catalogue->create(Constants::CompoundType);
    EXPECT_TRUE(dynamic_cast<CompoundItem*>(item.get()) != nullptr);
}

TEST_F(TestItemCatalogue, addLabeledItem)
{
    ItemCatalogue catalogue;
    catalogue.add<PropertyItem>("property");
    catalogue.add<VectorItem>("vector item");

    // checking model types and labels
    EXPECT_EQ(catalogue.modelTypes(), std::vector<std::string>({"Property", "Vector"}));
    EXPECT_EQ(catalogue.labels(), std::vector<std::string>({"property", "vector item"}));
}
