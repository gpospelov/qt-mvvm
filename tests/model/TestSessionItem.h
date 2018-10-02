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
    EXPECT_TRUE(item.modelType().empty());
}

TEST_F(TestSessionItem, value)
{
    SessionItem item;
    EXPECT_FALSE(item.data().isValid());

    QVariant expected(42.0);
    EXPECT_TRUE(item.setData(expected));
    EXPECT_EQ(item.data(), expected);

    SessionItem item2("Layer");
    EXPECT_EQ(item2.modelType(), "Layer");
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
    auto child4 = new SessionItem;

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

    // inserting forth item using index equal to number of items
    parent->insertItem(parent->childrenCount(), child4);

    // checking parents
    EXPECT_EQ(child1->parent(), parent.get());
    EXPECT_EQ(child2->parent(), parent.get());
    EXPECT_EQ(child3->parent(), parent.get());
    EXPECT_EQ(child4->parent(), parent.get());

    // attempt to insert same item twice
    EXPECT_THROW(parent->insertItem(-1, child2), std::runtime_error);

    // attempt to insert item using out of scope index
    auto child5 = new SessionItem;
    EXPECT_THROW(parent->insertItem(parent->childrenCount()+1, child5), std::runtime_error);
    delete child5;
}

TEST_F(TestSessionItem, takeRow)
{
    std::unique_ptr<SessionItem> parent(new SessionItem);
    auto child1 = new SessionItem;
    auto child2 = new SessionItem;
    auto child3 = new SessionItem;

    // inserting items
    parent->insertItem(-1, child1);
    parent->insertItem(-1, child2);
    parent->insertItem(-1, child3);

    // taking non-existing rows
    auto taken = parent->takeRow(-1);
    EXPECT_EQ(taken, nullptr);
    taken = parent->takeRow(parent->childrenCount());
    EXPECT_EQ(taken, nullptr);
    EXPECT_EQ(parent->childrenCount(), 3);

    // taking first row
    taken = parent->takeRow(0);
    EXPECT_EQ(taken->parent(), nullptr);
    std::vector<SessionItem*> expected = {child2, child3};
    EXPECT_EQ(parent->children(), expected);

    delete taken;
}

//TEST_F(TestSessionItem, littleTree)
//{
//    std::unique_ptr<SessionItem> parent(new SessionItem);
//    auto child1 = new SessionItem;
//    auto child2 = new SessionItem;
//    auto child3 = new SessionItem;

//    auto child11 = new SessionItem;
//    auto child12 = new SessionItem;
//    auto child31 = new SessionItem;
//    auto child32 = new SessionItem;

//    // creating tree
//    child1->insertItem(-1, child11);
//    child1->insertItem(-1, child12);
//    child3->insertItem(-1, child31);
//    child3->insertItem(-1, child32);

//    parent->insertItem(-1, child1);
//    parent->insertItem(-1, child2);
//    parent->insertItem(-1, child3);

//    // checking parents
//    EXPECT_EQ(parent->childrenCount(), 3);
//    EXPECT_EQ(child1->childrenCount(), 2);
//    EXPECT_EQ(child2->childrenCount(), 1);
//    EXPECT_EQ(child3->childrenCount(), 2);

//    EXPECT_EQ(child1->parent(), parent.get());
//    EXPECT_EQ(child2->parent(), parent.get());
//    EXPECT_EQ(child3->parent(), parent.get());

//    EXPECT_EQ(child11->parent(), child1);
//    EXPECT_EQ(child12->parent(), child1);
//    EXPECT_EQ(child31->parent(), child3);
//    EXPECT_EQ(child32->parent(), child3);

//    // take last row
//    auto taken = parent->takeRow(2);
//    EXPECT_EQ(taken, child3);
//    EXPECT_EQ(child3->parent(), nullptr);
//    EXPECT_EQ(child31->parent(), child3);
//    EXPECT_EQ(child32->parent(), child3);
//    delete taken;
//}


