// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/viewmodel/standardchildrenstrategies.h"

#include "google_test.h"
#include "toyitems.h"
#include "mvvm/model/compounditem.h"
#include "mvvm/model/propertyitem.h"
#include "mvvm/model/sessionitem.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/model/taginfo.h"
#include "mvvm/standarditems/vectoritem.h"

using namespace ModelView;

class StandardChildrenStrategiesTest : public ::testing::Test {
public:
    //! Helper class with two properties and one top level item on board.
    class TestItem : public CompoundItem {
    public:
        TestItem() : CompoundItem("test")
        {
            addProperty("length", 8.0);
            registerTag(TagInfo::universalTag("children"), /*set_as_default*/ true);
            insertItem<SessionItem>(TagRow::append());
            addProperty("height", 12.0);
        }
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
            result.push_back({child->modelType(), child->tagRow().tag});
        return result;
    }
};

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

//! Testing AllChildrenStrategy when one of children is hidden.
//! By the current convention this strategy still show all items.

TEST_F(StandardChildrenStrategiesTest, AllChildrenStrategyWhenHidden)
{
    AllChildrenStrategy strategy;
    VectorItem item;
    item.getItem(VectorItem::P_X)->setVisible(false);
    auto children = strategy.children(&item);
    EXPECT_EQ(children.size(), 3); // hidden items are still shown
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

//! Testing TopItemsStrategy when some items are hidden.

TEST_F(StandardChildrenStrategiesTest, TopItemsStrategyWhenHidden)
{
    TopItemsStrategy strategy;

    SessionModel model;
    auto vec1 = model.insertItem<VectorItem>();
    auto vec2 = model.insertItem<VectorItem>();
    vec2->setVisible(false);
    auto vec3 = model.insertItem<VectorItem>();

    auto children = strategy.children(model.rootItem());
    EXPECT_EQ(children, std::vector<SessionItem*>({vec1, vec3}));
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

//! Testing PropertyItemsStrategy when some items are hidden.

TEST_F(StandardChildrenStrategiesTest, PropertyItemsStrategyWhenHidden)
{
    PropertyItemsStrategy strategy;

    // VectorItem
    {
        VectorItem item;
        item.getItem(VectorItem::P_Y)->setVisible(false);
        auto children = strategy.children(&item);
        EXPECT_EQ(children.size(), 2);
    }

    // GroupItem
    {
        ToyItems::ShapeGroupItem item;
        item.setCurrentType(ToyItems::Constants::CylinderItemType);
        item.currentItem()->getItem(ToyItems::CylinderItem::P_RADIUS)->setVisible(false);
        auto children = strategy.children(&item);
        EXPECT_EQ(children.size(), 1);

        std::vector<ChildrenData> expected_children_data{
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
