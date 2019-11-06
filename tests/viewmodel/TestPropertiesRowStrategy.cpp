// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //


#include "google_test.h"
#include <mvvm/viewmodel/propertiesrowstrategy.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/standarditems/vectoritem.h>
#include <mvvm/viewmodel/viewdataitem.h>
#include "test_utils.h"

using namespace ModelView;

class TestPropertiesRowStrategy : public ::testing::Test
{
public:
    ~TestPropertiesRowStrategy();
};

TestPropertiesRowStrategy::~TestPropertiesRowStrategy() = default;

TEST_F(TestPropertiesRowStrategy, initialState)
{
    PropertiesRowStrategy strategy({});
    EXPECT_EQ(strategy.constructRow(nullptr).size(), 0);
    EXPECT_EQ(strategy.horizontalHeaderLabels(), QStringList());
}

//! Checks row construction for standard top level item. It shouldn't generate any rows.

TEST_F(TestPropertiesRowStrategy, topLevelItem)
{
    SessionItem item("model_type");

    PropertiesRowStrategy strategy({});
    auto items = strategy.constructRow(&item);
    EXPECT_EQ(items.size(), 0);
    EXPECT_EQ(strategy.horizontalHeaderLabels(), QStringList());

    TestUtils::clean_items(items);
}

//! Checks row construction for property item. It shouldn't generate any rows.

TEST_F(TestPropertiesRowStrategy, propertyItem)
{
    SessionItem item("model_type");
    item.setData(42.0);

    PropertiesRowStrategy strategy({});
    auto items = strategy.constructRow(&item);
    EXPECT_EQ(items.size(), 0);
    EXPECT_EQ(strategy.horizontalHeaderLabels(), QStringList());

    TestUtils::clean_items(items);
}

//! Checks row construction for vector item.
//! There should be 3 view items looking to x, y, z properties.

TEST_F(TestPropertiesRowStrategy, vectorItem)
{
    VectorItem item;

    EXPECT_EQ(item.property(VectorItem::P_X).value<double>(), 0.0);
    EXPECT_EQ(item.property(VectorItem::P_Y).value<double>(), 0.0);
    EXPECT_EQ(item.property(VectorItem::P_Z).value<double>(), 0.0);

    PropertiesRowStrategy strategy({"a", "b", "c"});
    auto items = strategy.constructRow(&item);

    EXPECT_EQ(items.size(), 3);
    EXPECT_EQ(strategy.horizontalHeaderLabels(), QStringList() << "a" << "b" << "c");

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

    TestUtils::clean_items(items);
}

//! Row construction for rootItem with single item inserted. Shouldn't generate any row.

TEST_F(TestPropertiesRowStrategy, baseItemInModelContext)
{
    SessionModel model;

    PropertiesRowStrategy strategy({});
    auto items = strategy.constructRow(model.rootItem());
    EXPECT_EQ(items.size(), 0);
    TestUtils::clean_items(items);

    model.insertItem<SessionItem>();
    items = strategy.constructRow(model.rootItem());
    EXPECT_EQ(items.size(), 0);

    TestUtils::clean_items(items);
}

//! Row construction for rootItem with single item inserted. Shouldn't generate any row.

TEST_F(TestPropertiesRowStrategy, propertyItemTree)
{
    SessionModel model;
    auto parent = model.insertItem<SessionItem>();

    parent->registerTag(TagInfo::universalTag("universal_tag"));
    parent->registerTag(TagInfo::propertyTag("property_tag", Constants::PropertyType));

    model.insertItem<SessionItem>(parent, "universal_tag");
    model.insertItem<PropertyItem>(parent, "property_tag");

    PropertiesRowStrategy strategy({});
    auto items = strategy.constructRow(model.rootItem());

    // root item doesn't have properties
    EXPECT_EQ(items.size(), 0);
    TestUtils::clean_items(items);

    // parent has one registered property.
    items = strategy.constructRow(parent);
    EXPECT_EQ(items.size(), 1);
    TestUtils::clean_items(items);
}

//! Row construction for rootItem when vectorItem is present. Shouldn't generate any row.

TEST_F(TestPropertiesRowStrategy, vectorItemInModelContext)
{
    SessionModel model;
    model.insertItem<VectorItem>();

    PropertiesRowStrategy strategy({});
    auto items = strategy.constructRow(model.rootItem());
    EXPECT_EQ(items.size(), 0);
    TestUtils::clean_items(items);
}
