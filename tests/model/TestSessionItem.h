#include <gtest/gtest.h>
#include "sessionitem.h"
#include <memory>

class TestSessionItem : public ::testing::Test
{
public:
    ~TestSessionItem();
};

TestSessionItem::~TestSessionItem() = default;

TEST_F(TestSessionItem, initialState)
{
    SessionItem item;

    EXPECT_EQ(item.model(), nullptr);
    EXPECT_EQ(item.parent(), nullptr);
    EXPECT_EQ(item.childrenCount(), 0);
    EXPECT_FALSE(item.data().isValid());
    EXPECT_TRUE(item.children().empty());
}

TEST_F(TestSessionItem, value)
{
    SessionItem item;
    EXPECT_FALSE(item.data().isValid());

    QVariant expected(42.0);
    EXPECT_TRUE(item.setData(expected));
    EXPECT_EQ(item.data(), expected);
}

TEST_F(TestSessionItem, insertItem)
{
    std::unique_ptr<SessionItem> parent(new SessionItem);
    std::unique_ptr<SessionItem> child(new SessionItem);

    // empty parent
    EXPECT_EQ(parent->childrenCount(), 0);
    EXPECT_EQ(parent->rowOfChild(nullptr), -1);
    EXPECT_EQ(parent->rowOfChild(child.get()), -1);
    EXPECT_EQ(parent->childAt(0), nullptr);
    EXPECT_EQ(parent->childAt(-1), nullptr);
    EXPECT_EQ(parent->childAt(10), nullptr);

    // inserting child
    auto p_child = child.release();
    parent->insertItem(0, p_child);
    EXPECT_EQ(parent->childrenCount(), 1);
    EXPECT_EQ(parent->rowOfChild(p_child), 0);
    EXPECT_EQ(parent->children()[0], p_child);
    EXPECT_EQ(parent->childAt(0), p_child);
    EXPECT_EQ(p_child->parent(), parent.get());

    // deleting child
    delete p_child;
    EXPECT_EQ(parent->childrenCount(), 1);
    EXPECT_EQ(parent->children()[0], nullptr);
}

TEST_F(TestSessionItem, insertChildren)
{
    std::unique_ptr<SessionItem> parent(new SessionItem);
    auto child1 = new SessionItem;
    auto child2 = new SessionItem;
    auto child3 = new SessionItem;

    // inserting two items
    parent->insertItem(-1, child1);
    parent->insertItem(-1, child2);
    EXPECT_EQ(parent->rowOfChild(child1), 0);
    EXPECT_EQ(parent->rowOfChild(child2), 1);
    EXPECT_EQ(parent->childAt(0), child1);
    EXPECT_EQ(parent->childAt(1), child2);
    std::vector<SessionItem*> expected = {child1, child2};
    EXPECT_EQ(parent->children(), expected);

    // inserting third item between two others
    parent->insertItem(1, child3);
    expected = {child1, child3, child2};
    EXPECT_EQ(parent->children(), expected);
    EXPECT_EQ(parent->rowOfChild(child1), 0);
    EXPECT_EQ(parent->rowOfChild(child2), 2);
    EXPECT_EQ(parent->rowOfChild(child3), 1);
    EXPECT_EQ(parent->childAt(0), child1);
    EXPECT_EQ(parent->childAt(1), child3);
    EXPECT_EQ(parent->childAt(2), child2);
    EXPECT_EQ(parent->childAt(3), nullptr);
}
