#include "google_test.h"
#include "labeldatarowconstructor.h"
#include "sessionitem.h"

using namespace ModelView;

class TestLabelDataRowConstructor : public ::testing::Test
{
public:
    ~TestLabelDataRowConstructor();
};

TestLabelDataRowConstructor::~TestLabelDataRowConstructor() = default;

TEST_F(TestLabelDataRowConstructor, initialState)
{
    LabelDataRowConstructor constructor;
    EXPECT_EQ(constructor.constructRow(nullptr).size(), 0);
}

//! Checks row construction for standard top level item, like Level, MultiLayer etc.

TEST_F(TestLabelDataRowConstructor, topLevelItem)
{
    std::unique_ptr<SessionItem> item(new SessionItem("model_type"));

    LabelDataRowConstructor constructor;
    auto items = constructor.constructRow(item.get());
    EXPECT_EQ(items.size(), 2); // label and empty items
}

//! Checks row construction for property item.

TEST_F(TestLabelDataRowConstructor, propertyItem)
{
    std::unique_ptr<SessionItem> item(new SessionItem("model_type"));
    item->setData(42.0, ItemDataRole::DATA);

    LabelDataRowConstructor constructor;
    auto items = constructor.constructRow(item.get());
    EXPECT_EQ(items.size(), 2);
}
