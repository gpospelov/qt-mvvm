#include <gtest/gtest.h>
#include "sessionmodel.h"
#include "sessionitem.h"
#include "itemutils.h"
#include <memory>

class TestItemUtils : public ::testing::Test
{
public:
    ~TestItemUtils();
};

TestItemUtils::~TestItemUtils() = default;

//! Simple iteration over item ahd its children

TEST_F(TestItemUtils, iterateItem)
{
    std::vector<const SessionItem*> visited_items;

    auto fun = [&](const SessionItem* item ) {
        visited_items.push_back(item);
    };

    // iteration over nullptr
    Utils::iterate(nullptr, fun);
    EXPECT_TRUE(visited_items.empty());

    // iteration over lonely parent
    std::unique_ptr<SessionItem> parent(new SessionItem);
    std::vector<const SessionItem*> expected = {parent.get()};
    Utils::iterate(parent.get(), fun);
    EXPECT_EQ(visited_items, expected);

    // adding children
    auto child1 = new SessionItem;
    auto child2 = new SessionItem;
    parent->insertItem(-1, child1);
    parent->insertItem(-1, child2);

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
    std::function<bool(const SessionItem*)> fun = [&](const SessionItem* item ) {
        visited_items.push_back(item);
        return false;
    };

    // iteration over lonely parent
    std::unique_ptr<SessionItem> parent(new SessionItem);
    auto child1 = new SessionItem;
    auto child2 = new SessionItem;
    parent->insertItem(-1, child1);
    parent->insertItem(-1, child2);

    std::vector<const SessionItem*> expected = {parent.get()};
    Utils::iterate_if(parent.get(), fun);
    EXPECT_EQ(visited_items, expected);
}

//! Iteration over root item of the model.

TEST_F(TestItemUtils, iterateModel)
{
    SessionModel model;

    // building model
    auto parent1 = model.insertNewItem();
    auto parent2 = model.insertNewItem();
    auto child1 = model.insertNewItem(parent1);
    auto child2 = model.insertNewItem(parent1);

    std::vector<const SessionItem*> visited_items;
    auto fun = [&](const SessionItem* item ) {
        visited_items.push_back(item);
    };

    // iteration
    Utils::iterate(model.rootItem(), fun);

    std::vector<const SessionItem*> expected = {model.rootItem(), parent1, child1, child2, parent2};
    EXPECT_EQ(visited_items, expected);
}
