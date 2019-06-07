#include "google_test.h"
#include "labeldatarowstrategy.h"
#include "sessionitem.h"
#include "viewlabelitem.h"
#include "viewdataitem.h"
#include "viewemptyitem.h"
#include "test_utils.h"

namespace  {
const int expected_column_count = 2;
const QStringList expected_labels = QStringList() << "Name" << "Value";
}

using namespace ModelView;

class TestLabelDataRowStrategy : public ::testing::Test
{
public:
    ~TestLabelDataRowStrategy();
};

TestLabelDataRowStrategy::~TestLabelDataRowStrategy() = default;

TEST_F(TestLabelDataRowStrategy, initialState)
{
    LabelDataRowStrategy constructor;
    EXPECT_EQ(constructor.constructRow(nullptr).size(), 0);
    EXPECT_EQ(constructor.horizontalHeaderLabels(), expected_labels);
}

//! Checks row construction for standard top level item, like Level, MultiLayer etc.

TEST_F(TestLabelDataRowStrategy, topLevelItem)
{
    SessionItem item("model_type");

    LabelDataRowStrategy constructor;
    auto items = constructor.constructRow(&item);
    EXPECT_EQ(items.size(), expected_column_count); // label and empty items
    EXPECT_EQ(constructor.horizontalHeaderLabels(), expected_labels);

    // checking that it is label and data
    auto labelItem = dynamic_cast<ViewLabelItem*>(items.at(0));
    auto emptyItem = dynamic_cast<ViewEmptyItem*>(items.at(1));
    ASSERT_TRUE(labelItem != nullptr);
    EXPECT_EQ(labelItem->item(), &item);
    ASSERT_TRUE(emptyItem != nullptr);
    EXPECT_EQ(emptyItem->item(), nullptr);

    TestUtils::clean_items(items);
}

//! Checks row construction for property item.

TEST_F(TestLabelDataRowStrategy, propertyItem)
{
    SessionItem item("model_type");
    item.setData(42.0, ItemDataRole::DATA);

    LabelDataRowStrategy constructor;
    auto items = constructor.constructRow(&item);
    EXPECT_EQ(items.size(), expected_column_count);
    EXPECT_EQ(constructor.horizontalHeaderLabels(), expected_labels);

    // checking that it is label and data
    auto labelItem = dynamic_cast<ViewLabelItem*>(items.at(0));
    auto dataItem = dynamic_cast<ViewDataItem*>(items.at(1));
    ASSERT_TRUE(labelItem != nullptr);
    EXPECT_EQ(labelItem->item(), &item);
    ASSERT_TRUE(dataItem != nullptr);
    EXPECT_EQ(dataItem->item(), &item);

    TestUtils::clean_items(items);
}
