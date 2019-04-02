#include "customvariants.h"
#include "google_test.h"
#include "itemutils.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "taginfo.h"
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
    parent->insertItem(child1);
    parent->insertItem(child2);

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
    parent->insertItem(child1);
    parent->insertItem(child2);

    std::vector<const SessionItem*> expected = {parent.get()};
    Utils::iterate_if(parent.get(), fun);
    EXPECT_EQ(visited_items, expected);
}

//! Iteration over root item of the model.

TEST_F(TestItemUtils, iterateModel)
{
    const model_type modelType = Constants::BaseType;
    SessionModel model;

    // building model
    auto parent1 = model.insertNewItem(modelType);
    auto parent2 = model.insertNewItem(modelType);
    parent1->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);
    parent2->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);
    auto child1 = model.insertNewItem(modelType, parent1);
    auto child2 = model.insertNewItem(modelType, parent1);

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

    auto parent = model.insertNewItem(Constants::BaseType);
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);

    const std::string model_a(Constants::BaseType);
    const std::string model_b(Constants::PropertyType);
    auto child1 = model.insertNewItem(model_a, parent);
    auto child2 = model.insertNewItem(model_a, parent);
    auto child3 = model.insertNewItem(model_b, parent);

    EXPECT_EQ(Utils::CopyNumber(child1), 0);
    EXPECT_EQ(Utils::CopyNumber(child2), 1);
    EXPECT_EQ(Utils::CopyNumber(child3), -1);
}
