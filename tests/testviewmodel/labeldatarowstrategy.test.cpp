// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "test_utils.h"
#include <mvvm/model/sessionitem.h>
#include <mvvm/viewmodel/labeldatarowstrategy.h>
#include <mvvm/viewmodel/standardviewitems.h>

namespace
{
const int expected_column_count = 2;
const QStringList expected_labels = QStringList() << "Name"
                                                  << "Value";
} // namespace

using namespace ModelView;

class LabelDataRowStrategyTest : public ::testing::Test
{
public:
    ~LabelDataRowStrategyTest();
};

LabelDataRowStrategyTest::~LabelDataRowStrategyTest() = default;

TEST_F(LabelDataRowStrategyTest, initialState)
{
    LabelDataRowStrategy constructor;
    EXPECT_EQ(constructor.constructRow(nullptr).size(), 0);
    EXPECT_EQ(constructor.horizontalHeaderLabels(), expected_labels);
}

//! Checks row construction for standard top level item, like Level, MultiLayer etc.

TEST_F(LabelDataRowStrategyTest, topLevelItem)
{
    SessionItem item("model_type");

    LabelDataRowStrategy constructor;
    auto items = constructor.constructRow(&item);
    EXPECT_EQ(items.size(), expected_column_count); // label and empty items
    EXPECT_EQ(constructor.horizontalHeaderLabels(), expected_labels);

    // checking that it is label and data
    auto labelItem = dynamic_cast<ViewLabelItem*>(items.at(0).get());
    auto dataItem = dynamic_cast<ViewDataItem*>(items.at(1).get());
    ASSERT_TRUE(labelItem != nullptr);
    EXPECT_EQ(labelItem->item(), &item);
    ASSERT_TRUE(dataItem != nullptr);
    EXPECT_EQ(dataItem->item(), &item);
}

//! Checks row construction for property item.

TEST_F(LabelDataRowStrategyTest, propertyItem)
{
    SessionItem item("model_type");
    item.setData(42.0);

    LabelDataRowStrategy constructor;
    auto items = constructor.constructRow(&item);
    EXPECT_EQ(items.size(), expected_column_count);
    EXPECT_EQ(constructor.horizontalHeaderLabels(), expected_labels);

    // checking that it is label and data
    auto labelItem = dynamic_cast<ViewLabelItem*>(items.at(0).get());
    auto dataItem = dynamic_cast<ViewDataItem*>(items.at(1).get());
    ASSERT_TRUE(labelItem != nullptr);
    EXPECT_EQ(labelItem->item(), &item);
    ASSERT_TRUE(dataItem != nullptr);
    EXPECT_EQ(dataItem->item(), &item);
}
