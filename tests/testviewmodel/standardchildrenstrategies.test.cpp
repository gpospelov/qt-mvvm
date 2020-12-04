// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "toyitems.h"
#include "toymodel.h"
#include <mvvm/model/compounditem.h>
#include <mvvm/model/propertyitem.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/taginfo.h>
#include <mvvm/standarditems/vectoritem.h>
#include <mvvm/viewmodel/standardchildrenstrategies.h>

using namespace ModelView;

class StandardChildrenStrategiesTest : public ::testing::Test
{
public:
    ~StandardChildrenStrategiesTest();

    //! Helper class with two properties and one top level item on board.
    class TestItem : public CompoundItem
    {
    public:
        TestItem() : CompoundItem("test")
        {
            addProperty("length", 8.0);
            registerTag(TagInfo::universalTag("children"), /*set_as_default*/ true);
            insertItem(new SessionItem, TagRow::append());
            addProperty("height", 12.0);
        }
        ~TestItem();
    };

    struct ChildrenData {
        std::string model_type;
        std::string tag;
        bool operator==(const ChildrenData& other) const
        {
            return model_type == other.model_type && tag == other.tag;
        }
    };

    std::vector<ChildrenData> children_data(std::vector<SessionItem*> children)
    {
        std::vector<ChildrenData> result;
        for (auto child : children)
            result.push_back({child->modelType(), child->tag()});
        return result;
    }
};

StandardChildrenStrategiesTest::~StandardChildrenStrategiesTest() = default;
StandardChildrenStrategiesTest::TestItem::~TestItem() = default;

//! Testing AllChildrenStrategy.

TEST_F(StandardChildrenStrategiesTest, AllChildrenStrategy)
{
    AllChildrenStrategy strategy;

    // nullptr
    auto children = strategy.children(nullptr);
    EXPECT_EQ(children.size(), 0);

    // empty item
    SessionItem item1("model_type");
    children = strategy.children(&item1);
    EXPECT_EQ(children.size(), 0);

    // VectorItem
    VectorItem item2;
    children = strategy.children(&item2);
    EXPECT_EQ(children.size(), 3);

    // CompoundItem
    CompoundItem item3;
    item3.addProperty("height", 42.0);
    children = strategy.children(&item3);
    EXPECT_EQ(children.size(), 1);

    // TestItem
    TestItem item4;
    children = strategy.children(&item4);
    EXPECT_EQ(children.size(), 3);

    // GroupItem
    ToyItems::ShapeGroupItem item5;
    item5.setCurrentType(ToyItems::Constants::CylinderItemType);
    children = strategy.children(&item5);
    EXPECT_EQ(children.size(), 3); // number of registered children
}

//! Testing TopItemsStrategy.

TEST_F(StandardChildrenStrategiesTest, TopItemsStrategy)
{
    TopItemsStrategy strategy;

    // nullptr
    auto children = strategy.children(nullptr);
    EXPECT_EQ(children.size(), 0);

    // empty item
    SessionItem item1("model_type");
    children = strategy.children(&item1);
    EXPECT_EQ(children.size(), 0);

    // VectorItem
    VectorItem item2;
    children = strategy.children(&item2);
    EXPECT_EQ(children.size(), 0);

    // CompoundItem
    CompoundItem item3;
    item3.addProperty("height", 42.0);
    children = strategy.children(&item3);
    EXPECT_EQ(children.size(), 0);

    // TestItem
    TestItem item4;
    children = strategy.children(&item4);
    EXPECT_EQ(children.size(), 1);

    // GroupItem
    ToyItems::ShapeGroupItem item5;
    item5.setCurrentType(ToyItems::Constants::CylinderItemType);
    children = strategy.children(&item5);
    EXPECT_EQ(children.size(), 3); // number of registered children
}

//! Testing PropertyItemsStrategy.

TEST_F(StandardChildrenStrategiesTest, PropertyItemsStrategy)
{
    PropertyItemsStrategy strategy;

    // nullptr
    {
        auto children = strategy.children(nullptr);
        EXPECT_EQ(children.size(), 0);
    }

    // empty item
    {
        SessionItem item("model_type");
        auto children = strategy.children(&item);
        EXPECT_EQ(children.size(), 0);
    }

    // VectorItem
    {
        VectorItem item;
        auto children = strategy.children(&item);
        EXPECT_EQ(children.size(), 3);
    }

    // CompoundItem
    {
        CompoundItem item;
        item.addProperty("height", 42.0);
        auto children = strategy.children(&item);
        EXPECT_EQ(children.size(), 1);
    }

    // TestItem
    {
        TestItem item;
        auto children = strategy.children(&item);
        EXPECT_EQ(children.size(), 2);
    }

    // GroupItem
    {
        ToyItems::ShapeGroupItem item;
        item.setCurrentType(ToyItems::Constants::CylinderItemType);
        auto children = strategy.children(&item);
        EXPECT_EQ(children.size(), 2);

        std::vector<ChildrenData> expected_children_data{
            {Constants::PropertyType, ToyItems::CylinderItem::P_RADIUS},
            {Constants::PropertyType, ToyItems::CylinderItem::P_HEIGHT}};
        EXPECT_EQ(children_data(children), expected_children_data);
    }
}

//! Testing PropertyItemsFlatStrategy.

TEST_F(StandardChildrenStrategiesTest, PropertyItemsFlatStrategy)
{
    PropertyItemsFlatStrategy strategy;

    // nullptr
    {
        auto children = strategy.children(nullptr);
        EXPECT_EQ(children.size(), 0);
    }

    // empty item
    {
        SessionItem item("model_type");
        auto children = strategy.children(&item);
        EXPECT_EQ(children.size(), 0);
    }

    // VectorItem
    {
        VectorItem item;
        auto children = strategy.children(&item);
        EXPECT_EQ(children.size(), 3);
    }

    // CompoundItem
    {
        CompoundItem item;
        item.addProperty("height", 42.0);
        auto children = strategy.children(&item);
        EXPECT_EQ(children.size(), 1);
    }

    // TestItem
    {
        TestItem item;
        auto children = strategy.children(&item);
        EXPECT_EQ(children.size(), 2);
    }

    // GroupItem
    {
        ToyItems::ShapeGroupItem item;
        item.setCurrentType(ToyItems::Constants::CylinderItemType);
        auto children = strategy.children(&item);
        EXPECT_EQ(children.size(), 2);

        std::vector<ChildrenData> expected_children_data{
            {Constants::PropertyType, ToyItems::CylinderItem::P_RADIUS},
            {Constants::PropertyType, ToyItems::CylinderItem::P_HEIGHT}};
        EXPECT_EQ(children_data(children), expected_children_data);
    }

    // ParticleItem
    {
        ToyItems::ParticleItem item;
        auto children = strategy.children(&item);
        EXPECT_EQ(children.size(), 3);

        std::vector<ChildrenData> expected_children_data{
            {Constants::VectorItemType, ToyItems::ParticleItem::P_POSITION},
            {ToyItems::Constants::ShapeGroupItemType, ToyItems::ParticleItem::P_SHAPES},
            {Constants::PropertyType, ToyItems::SphereItem::P_RADIUS}};

        EXPECT_EQ(children_data(children), expected_children_data);
    }
}
