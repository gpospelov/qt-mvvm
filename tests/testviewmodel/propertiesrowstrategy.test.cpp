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
#include <mvvm/model/sessionmodel.h>
#include <mvvm/standarditems/vectoritem.h>
#include <mvvm/viewmodel/propertiesrowstrategy.h>
#include <mvvm/viewmodel/standardviewitems.h>

using namespace ModelView;

class PropertiesRowStrategyTest : public ::testing::Test
{
public:
    ~PropertiesRowStrategyTest();
};

PropertiesRowStrategyTest::~PropertiesRowStrategyTest() = default;

TEST_F(PropertiesRowStrategyTest, initialState)
{
    PropertiesRowStrategy strategy;
    EXPECT_EQ(strategy.constructRow(nullptr).size(), 0);
    EXPECT_EQ(strategy.horizontalHeaderLabels(), QStringList());
}

//! Checks row construction for standard top level item. It shouldn't generate any rows.

TEST_F(PropertiesRowStrategyTest, topLevelItem)
{
    SessionItem item("model_type");

    PropertiesRowStrategy strategy;
    auto items = strategy.constructRow(&item);
    EXPECT_EQ(items.size(), 0);
    EXPECT_EQ(strategy.horizontalHeaderLabels(), QStringList());
}

//! Checks row construction for property item. It shouldn't generate any rows.

TEST_F(PropertiesRowStrategyTest, propertyItem)
{
    SessionItem item("model_type");
    item.setData(42.0);

    PropertiesRowStrategy strategy;
    auto items = strategy.constructRow(&item);
    EXPECT_EQ(items.size(), 0);
    EXPECT_EQ(strategy.horizontalHeaderLabels(), QStringList());
}

//! Checks row construction for vector item.
//! There should be 3 view items looking to x, y, z properties.

TEST_F(PropertiesRowStrategyTest, vectorItemCustomLabels)
{
    VectorItem item;

    EXPECT_EQ(item.property<double>(VectorItem::P_X), 0.0);
    EXPECT_EQ(item.property<double>(VectorItem::P_Y), 0.0);
    EXPECT_EQ(item.property<double>(VectorItem::P_Z), 0.0);

    PropertiesRowStrategy strategy({"a", "b", "c"});
    auto items = strategy.constructRow(&item);

    EXPECT_EQ(items.size(), 3);
    EXPECT_EQ(strategy.horizontalHeaderLabels(), QStringList() << "a"
                                                               << "b"
                                                               << "c");

    // views should look at 3 property items
    auto view_x = items.at(0).get();
    EXPECT_EQ(view_x->item(), item.getItem(VectorItem::P_X));

    auto view_y = items.at(1).get();
    EXPECT_EQ(view_y->item(), item.getItem(VectorItem::P_Y));

    auto view_z = items.at(2).get();
    EXPECT_EQ(view_z->item(), item.getItem(VectorItem::P_Z));
}

//! Checks row label construction for vector item.

TEST_F(PropertiesRowStrategyTest, vectorItemAutoLabels)
{
    VectorItem item;

    EXPECT_EQ(item.property<double>(VectorItem::P_X), 0.0);
    EXPECT_EQ(item.property<double>(VectorItem::P_Y), 0.0);
    EXPECT_EQ(item.property<double>(VectorItem::P_Z), 0.0);

    QStringList expected = QStringList() << "X"
                                         << "Y"
                                         << "Z";

    PropertiesRowStrategy strategy;
    auto items = strategy.constructRow(&item);
    EXPECT_EQ(strategy.horizontalHeaderLabels(), expected);
}

//! Row construction for rootItem with single item inserted. Shouldn't generate any row.

TEST_F(PropertiesRowStrategyTest, baseItemInModelContext)
{
    SessionModel model;

    PropertiesRowStrategy strategy;
    auto items = strategy.constructRow(model.rootItem());
    EXPECT_EQ(items.size(), 0);

    model.insertItem<SessionItem>();
    items = strategy.constructRow(model.rootItem());
    EXPECT_EQ(items.size(), 0);
}

//! Row construction for rootItem with single item inserted. Shouldn't generate any row.

TEST_F(PropertiesRowStrategyTest, propertyItemTree)
{
    SessionModel model;
    auto parent = model.insertItem<SessionItem>();

    parent->registerTag(TagInfo::universalTag("universal_tag"));
    parent->registerTag(TagInfo::propertyTag("property_tag", Constants::PropertyType));

    model.insertItem<SessionItem>(parent, "universal_tag");
    model.insertItem<PropertyItem>(parent, "property_tag");

    PropertiesRowStrategy strategy;
    auto items = strategy.constructRow(model.rootItem());

    // root item doesn't have properties
    EXPECT_EQ(items.size(), 0);

    // parent has one registered property.
    items = strategy.constructRow(parent);
    EXPECT_EQ(items.size(), 1);
}

//! Row construction for rootItem when vectorItem is present. Shouldn't generate any row.

TEST_F(PropertiesRowStrategyTest, vectorItemInModelContext)
{
    SessionModel model;
    model.insertItem<VectorItem>();

    PropertiesRowStrategy strategy;
    auto items = strategy.constructRow(model.rootItem());
    EXPECT_EQ(items.size(), 0);
}
