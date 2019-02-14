#include "google_test.h"
#include "rowconstructor.h"
#include "sessionitem.h"

using namespace ModelView;

class TestRowConstructor : public ::testing::Test
{
public:
    ~TestRowConstructor();
};

TestRowConstructor::~TestRowConstructor() = default;

TEST_F(TestRowConstructor, initialState)
{
    DefaultRowConstructor constructor;
    EXPECT_EQ(constructor.constructRow(nullptr).size(), 0);
}

//! Checks row construction for standard top level item, like Level, MultiLayer etc.

TEST_F(TestRowConstructor, topLevelItem)
{
    std::unique_ptr<SessionItem> item(new SessionItem("model_type"));

    DefaultRowConstructor constructor;
    auto items = constructor.constructRow(item.get());
    EXPECT_EQ(items.size(), 1);
}

//! Checks row construction for property item.

TEST_F(TestRowConstructor, propertyItem)
{
    std::unique_ptr<SessionItem> item(new SessionItem("model_type"));
    item->setData(42.0, ItemDataRole::DATA);

    DefaultRowConstructor constructor;
    auto items = constructor.constructRow(item.get());
    EXPECT_EQ(items.size(), 2);
}
