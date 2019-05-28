#include "google_test.h"
#include "propertiesrowconstructor.h"
#include "sessionitem.h"
#include "vectoritem.h"
#include "viewdataitem.h"

using namespace ModelView;

class TestPropertiesRowConstructor : public ::testing::Test
{
public:
    ~TestPropertiesRowConstructor();
};

TestPropertiesRowConstructor::~TestPropertiesRowConstructor() = default;

TEST_F(TestPropertiesRowConstructor, initialState)
{
    PropertiesRowConstructor constructor({});
    EXPECT_EQ(constructor.constructRow(nullptr).size(), 0);
    EXPECT_EQ(constructor.columnCount(), 0);
    EXPECT_EQ(constructor.horizontalHeaderLabels(), QStringList());
}

//! Checks row construction for standard top level item. It shouldn't generate any rows.

TEST_F(TestPropertiesRowConstructor, topLevelItem)
{
    std::unique_ptr<SessionItem> item(new SessionItem("model_type"));

    PropertiesRowConstructor constructor({});
    auto items = constructor.constructRow(item.get());
    EXPECT_EQ(items.size(), 0);
    EXPECT_EQ(constructor.columnCount(), 0);
    EXPECT_EQ(constructor.horizontalHeaderLabels(), QStringList());
}

//! Checks row construction for property item. It shouldn't generate any rows.

TEST_F(TestPropertiesRowConstructor, propertyItem)
{
    std::unique_ptr<SessionItem> item(new SessionItem("model_type"));
    item->setData(42.0, ItemDataRole::DATA);

    PropertiesRowConstructor constructor({});
    auto items = constructor.constructRow(item.get());
    EXPECT_EQ(items.size(), 0);
    EXPECT_EQ(constructor.columnCount(), 0);
    EXPECT_EQ(constructor.horizontalHeaderLabels(), QStringList());
}

//! Checks row construction for vector item.
//! There should be 3 view items looking to x, y, z properties.

TEST_F(TestPropertiesRowConstructor, vectorItem)
{
    VectorItem item;

    EXPECT_EQ(item.getItemValue(VectorItem::P_X).toDouble(), 0.0);
    EXPECT_EQ(item.getItemValue(VectorItem::P_Y).toDouble(), 0.0);
    EXPECT_EQ(item.getItemValue(VectorItem::P_Z).toDouble(), 0.0);

    PropertiesRowConstructor constructor({"a", "b", "c"});
    auto items = constructor.constructRow(&item);

    EXPECT_EQ(items.size(), 3);
    EXPECT_EQ(constructor.columnCount(), 3);
    EXPECT_EQ(constructor.horizontalHeaderLabels(), QStringList() << "a" << "b" << "c");

    // views should look at 3 property items
    auto view_x = dynamic_cast<ViewDataItem*>(items.at(0));
    ASSERT_TRUE(view_x != nullptr);
    EXPECT_EQ(view_x->item(), item.getItem(VectorItem::P_X));

    auto view_y = dynamic_cast<ViewDataItem*>(items.at(1));
    ASSERT_TRUE(view_y != nullptr);
    EXPECT_EQ(view_y->item(), item.getItem(VectorItem::P_Y));

    auto view_z = dynamic_cast<ViewDataItem*>(items.at(2));
    ASSERT_TRUE(view_z != nullptr);
    EXPECT_EQ(view_z->item(), item.getItem(VectorItem::P_Z));
}
