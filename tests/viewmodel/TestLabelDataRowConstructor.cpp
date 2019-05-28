#include "google_test.h"
#include "labeldatarowconstructor.h"
#include "sessionitem.h"
#include "viewlabelitem.h"
#include "viewdataitem.h"
#include "viewemptyitem.h"

namespace  {
const int expected_column_count = 2;
const QStringList expected_labels = QStringList() << "Name" << "Value";
}

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
    EXPECT_EQ(constructor.columnCount(), expected_column_count);
    EXPECT_EQ(constructor.horizontalHeaderLabels(), expected_labels);
}

//! Checks row construction for standard top level item, like Level, MultiLayer etc.

TEST_F(TestLabelDataRowConstructor, topLevelItem)
{
    std::unique_ptr<SessionItem> item(new SessionItem("model_type"));

    LabelDataRowConstructor constructor;
    auto items = constructor.constructRow(item.get());
    EXPECT_EQ(items.size(), expected_column_count); // label and empty items
    EXPECT_EQ(constructor.columnCount(), expected_column_count);
    EXPECT_EQ(constructor.horizontalHeaderLabels(), expected_labels);

    // checking that it is label and data
    auto labelItem = dynamic_cast<ViewLabelItem*>(items.at(0));
    auto emptyItem = dynamic_cast<ViewEmptyItem*>(items.at(1));
    ASSERT_TRUE(labelItem != nullptr);
    EXPECT_EQ(labelItem->item(), item.get());
    ASSERT_TRUE(emptyItem != nullptr);
    EXPECT_EQ(emptyItem->item(), item.get());
}

//! Checks row construction for property item.

TEST_F(TestLabelDataRowConstructor, propertyItem)
{
    std::unique_ptr<SessionItem> item(new SessionItem("model_type"));
    item->setData(42.0, ItemDataRole::DATA);

    LabelDataRowConstructor constructor;
    auto items = constructor.constructRow(item.get());
    EXPECT_EQ(items.size(), expected_column_count);
    EXPECT_EQ(constructor.columnCount(), expected_column_count);
    EXPECT_EQ(constructor.horizontalHeaderLabels(), expected_labels);

    // checking that it is label and data
    auto labelItem = dynamic_cast<ViewLabelItem*>(items.at(0));
    auto dataItem = dynamic_cast<ViewEmptyItem*>(items.at(1));
    ASSERT_TRUE(labelItem != nullptr);
    EXPECT_EQ(labelItem->item(), item.get());
    ASSERT_TRUE(dataItem != nullptr);
    EXPECT_EQ(dataItem->item(), item.get());
}
