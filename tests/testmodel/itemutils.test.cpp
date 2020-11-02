// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <memory>
#include <mvvm/model/customvariants.h>
#include <mvvm/model/itemutils.h>
#include <mvvm/model/propertyitem.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/model/taginfo.h>
#include <mvvm/standarditems/vectoritem.h>

using namespace ModelView;

class ItemUtilsTest : public ::testing::Test
{
public:
    ~ItemUtilsTest();
};

ItemUtilsTest::~ItemUtilsTest() = default;

//! Simple iteration over item and its children

TEST_F(ItemUtilsTest, iterateItem)
{
    std::vector<const SessionItem*> visited_items;

    auto fun = [&](const SessionItem* item) { visited_items.push_back(item); };

    // iteration over nullptr
    Utils::iterate(nullptr, fun);
    EXPECT_TRUE(visited_items.empty());

    // iteration over lonely parent
    std::unique_ptr<SessionItem> parent(new SessionItem);
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);

    std::vector<const SessionItem*> expected = {parent.get()};
    Utils::iterate(parent.get(), fun);
    EXPECT_EQ(visited_items, expected);

    // adding children
    auto child1 = new SessionItem;
    auto child2 = new SessionItem;
    parent->insertItem(child1, TagRow::append());
    parent->insertItem(child2, TagRow::append());

    visited_items.clear();
    Utils::iterate(parent.get(), fun);

    expected = {parent.get(), child1, child2};
    EXPECT_EQ(visited_items, expected);
}

//! Conditional iteration over item and its children.

TEST_F(ItemUtilsTest, iterateIfItem)
{
    std::vector<const SessionItem*> visited_items;

    // function which will not let iterate over children
    std::function<bool(const SessionItem*)> fun = [&](const SessionItem* item) {
        visited_items.push_back(item);
        return false;
    };

    // iteration over lonely parent
    std::unique_ptr<SessionItem> parent(new SessionItem);
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);

    auto child1 = new SessionItem;
    auto child2 = new SessionItem;
    parent->insertItem(child1, TagRow::append());
    parent->insertItem(child2, TagRow::append());

    std::vector<const SessionItem*> expected = {parent.get()};
    Utils::iterate_if(parent.get(), fun);
    EXPECT_EQ(visited_items, expected);
}

//! Iteration over root item of the model.

TEST_F(ItemUtilsTest, iterateModel)
{
    SessionModel model;

    // building model
    auto parent1 = model.insertItem<SessionItem>();
    auto parent2 = model.insertItem<SessionItem>();
    parent1->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);
    parent2->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);
    auto child1 = model.insertItem<SessionItem>(parent1);
    auto child2 = model.insertItem<SessionItem>(parent1);

    std::vector<const SessionItem*> visited_items;
    auto fun = [&](const SessionItem* item) { visited_items.push_back(item); };

    // iteration
    Utils::iterate(model.rootItem(), fun);

    std::vector<const SessionItem*> expected = {model.rootItem(), parent1, child1, child2, parent2};
    EXPECT_EQ(visited_items, expected);
}

//! Copy number of child in parents tree.

TEST_F(ItemUtilsTest, itemCopyNumber)
{
    SessionModel model;

    auto parent = model.insertItem<SessionItem>();
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);

    auto child1 = model.insertItem<SessionItem>(parent);
    auto child2 = model.insertItem<SessionItem>(parent);
    auto child3 = model.insertItem<PropertyItem>(parent);

    EXPECT_EQ(Utils::CopyNumber(child1), 0);
    EXPECT_EQ(Utils::CopyNumber(child2), 1);
    EXPECT_EQ(Utils::CopyNumber(child3), -1);
}

//! Check access to top level and property items.

TEST_F(ItemUtilsTest, TopLevelItems)
{
    SessionModel model;

    auto parent = model.insertItem<SessionItem>();
    parent->registerTag(TagInfo::universalTag("default_tag"), /*set_as_default*/ true);
    parent->registerTag(TagInfo::propertyTag("property_tag", Constants::PropertyType));

    auto child1 = model.insertItem<SessionItem>(parent, "default_tag");
    model.insertItem<PropertyItem>(parent, "property_tag");
    auto child3 = model.insertItem<SessionItem>(parent, "default_tag");

    EXPECT_EQ(Utils::TopLevelItems(*model.rootItem()), std::vector<SessionItem*>({parent}));
    EXPECT_EQ(Utils::TopLevelItems(*child1), std::vector<SessionItem*>({}));
    EXPECT_EQ(Utils::TopLevelItems(*parent), std::vector<SessionItem*>({child1, child3}));
}

//! Check access to top level and property items.

TEST_F(ItemUtilsTest, SinglePropertyItems)
{
    SessionModel model;

    auto parent = model.insertItem<SessionItem>();
    parent->registerTag(TagInfo::universalTag("default_tag"), /*set_as_default*/ true);
    parent->registerTag(TagInfo::propertyTag("property_tag", Constants::PropertyType));

    auto child1 = model.insertItem<SessionItem>(parent, "default_tag");
    auto child2 = model.insertItem<PropertyItem>(parent, "property_tag");
    model.insertItem<SessionItem>(parent, "default_tag");

    EXPECT_EQ(Utils::SinglePropertyItems(*model.rootItem()), std::vector<SessionItem*>({}));
    EXPECT_EQ(Utils::SinglePropertyItems(*child1), std::vector<SessionItem*>({}));
    EXPECT_EQ(Utils::SinglePropertyItems(*parent), std::vector<SessionItem*>({child2}));
}

//! Looking for next item.

TEST_F(ItemUtilsTest, FindNextSibling)
{
    SessionModel model;

    auto parent = model.insertItem<SessionItem>();
    parent->registerTag(TagInfo::universalTag("default_tag"), /*set_as_default*/ true);
    parent->registerTag(TagInfo::propertyTag("property_tag", Constants::PropertyType));

    auto property = model.insertItem<PropertyItem>(parent, "property_tag");
    auto child0 = model.insertItem<SessionItem>(parent, "default_tag");
    auto child1 = model.insertItem<SessionItem>(parent, "default_tag");
    auto child2 = model.insertItem<SessionItem>(parent, "default_tag");

    EXPECT_EQ(Utils::FindNextSibling(child0), child1);
    EXPECT_EQ(Utils::FindNextSibling(child1), child2);
    EXPECT_EQ(Utils::FindNextSibling(child2), nullptr);
    EXPECT_EQ(Utils::FindNextSibling(property), nullptr);
    EXPECT_EQ(Utils::FindNextSibling(parent), nullptr);
}

//! Looking for previous item.

TEST_F(ItemUtilsTest, FindPreviousSibling)
{
    SessionModel model;

    auto parent = model.insertItem<SessionItem>();
    parent->registerTag(TagInfo::universalTag("default_tag"), /*set_as_default*/ true);
    parent->registerTag(TagInfo::propertyTag("property_tag", Constants::PropertyType));

    auto property = model.insertItem<PropertyItem>(parent, "property_tag");
    auto child0 = model.insertItem<SessionItem>(parent, "default_tag");
    auto child1 = model.insertItem<SessionItem>(parent, "default_tag");
    auto child2 = model.insertItem<SessionItem>(parent, "default_tag");

    EXPECT_EQ(Utils::FindPreviousSibling(child0), nullptr);
    EXPECT_EQ(Utils::FindPreviousSibling(child1), child0);
    EXPECT_EQ(Utils::FindPreviousSibling(child2), child1);
    EXPECT_EQ(Utils::FindPreviousSibling(property), nullptr);
    EXPECT_EQ(Utils::FindPreviousSibling(parent), nullptr);
}

//! Looking for previous item.

TEST_F(ItemUtilsTest, FindNextItemToSelect)
{
    SessionModel model;

    auto parent = model.insertItem<SessionItem>();
    parent->registerTag(TagInfo::universalTag("default_tag"), /*set_as_default*/ true);
    parent->registerTag(TagInfo::propertyTag("property_tag", Constants::PropertyType));

    auto property = model.insertItem<PropertyItem>(parent, "property_tag");
    auto child0 = model.insertItem<SessionItem>(parent, "default_tag");
    auto child1 = model.insertItem<SessionItem>(parent, "default_tag");
    auto child2 = model.insertItem<SessionItem>(parent, "default_tag");

    EXPECT_EQ(Utils::FindNextItemToSelect(child0), child1);
    EXPECT_EQ(Utils::FindNextItemToSelect(child1), child2);
    EXPECT_EQ(Utils::FindNextItemToSelect(child2), child1);
    EXPECT_EQ(Utils::FindNextItemToSelect(property), parent);
    EXPECT_EQ(Utils::FindNextItemToSelect(parent), model.rootItem());
}

//! Looking for previous item.

TEST_F(ItemUtilsTest, IsItemAncestor)
{
    SessionModel model;
    EXPECT_FALSE(Utils::IsItemAncestor(model.rootItem(), model.rootItem()));

    // rootItem in ancestor of vectorItem, but not vice versa
    auto vector_item = model.insertItem<VectorItem>();
    EXPECT_TRUE(Utils::IsItemAncestor(vector_item, model.rootItem()));
    EXPECT_FALSE(Utils::IsItemAncestor(model.rootItem(), vector_item));

    auto x_item = vector_item->getItem(VectorItem::P_X);

    EXPECT_TRUE(Utils::IsItemAncestor(x_item, model.rootItem()));
    EXPECT_TRUE(Utils::IsItemAncestor(x_item, vector_item));
    EXPECT_FALSE(Utils::IsItemAncestor(model.rootItem(), x_item));
    EXPECT_FALSE(Utils::IsItemAncestor(vector_item, x_item));

    auto y_item = vector_item->getItem(VectorItem::P_Y);
    EXPECT_FALSE(Utils::IsItemAncestor(x_item, y_item));
}

TEST_F(ItemUtilsTest, UniqueItems)
{
    SessionModel model;
    auto item0 = model.insertItem<SessionItem>(model.rootItem());
    auto item1 = model.insertItem<SessionItem>(model.rootItem());
    auto item2 = model.insertItem<SessionItem>(model.rootItem());
    std::vector<SessionItem*> data = {nullptr, item0, item1, item2, item0, item2, nullptr};
    std::vector<SessionItem*> expected = {item0, item1, item2};
    EXPECT_EQ(Utils::UniqueItems(data), expected);
}

TEST_F(ItemUtilsTest, CastedItems)
{
    SessionModel model;
    auto item0 = model.insertItem<SessionItem>(model.rootItem());
    auto item1 = model.insertItem<PropertyItem>(model.rootItem());
    auto item2 = model.insertItem<VectorItem>(model.rootItem());
    std::vector<SessionItem*> data = {nullptr, item0, item1, item2, item0, item1, item2, nullptr};

    EXPECT_EQ(Utils::CastedItems<PropertyItem>(data), std::vector<PropertyItem*>({item1, item1}));
}
