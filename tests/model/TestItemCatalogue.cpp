#include "google_test.h"
#include "itemcatalogue.h"
#include "propertyitem.h"

using namespace ModelView;

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
    EXPECT_FALSE(dynamic_cast<PropertyItem*>(item.get()) == nullptr);
}
