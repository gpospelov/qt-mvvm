#include <mvvm/model/customvariants.h>
#include "google_test.h"
#include <mvvm/model/itemutils.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/model/propertyitem.h>
#include <mvvm/model/taginfo.h>
#include <memory>

using namespace ModelView;

class TestItemUtils : public ::testing::Test
{
public:
    ~TestItemUtils();
};

TestItemUtils::~TestItemUtils() = default;

//! Simple iteration over item and its children

TEST_F(TestItemUtils, iterateItem)
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

TEST_F(TestItemUtils, iterateIfItem)
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

TEST_F(TestItemUtils, iterateModel)
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

TEST_F(TestItemUtils, itemCopyNumber)
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

TEST_F(TestItemUtils, TopLevelAndPropertyItems)
{
    SessionModel model;

    auto parent = model.insertItem<SessionItem>();
    parent->registerTag(TagInfo::universalTag("default_tag"), /*set_as_default*/ true);
    parent->registerTag(TagInfo::propertyTag("property_tag", Constants::PropertyType));

    auto child1 = model.insertItem<SessionItem>(parent, "default_tag", -1);
    auto child2 = model.insertItem<PropertyItem>(parent, "property_tag", -1);
    auto child3 = model.insertItem<SessionItem>(parent, "default_tag", -1);

    EXPECT_EQ(Utils::TopLevelItems(*parent), std::vector<SessionItem*>({child1, child3}));
    EXPECT_EQ(Utils::SinglePropertyItems(*parent), std::vector<SessionItem*>({child2}));
}
