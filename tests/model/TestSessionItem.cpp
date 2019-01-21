#include "google_test.h"
#include "test_utils.h"
#include "sessionitem.h"
#include "itempool.h"
#include "taginfo.h"
#include <memory>

using namespace ModelView;

class TestSessionItem : public ::testing::Test
{
public:
    ~TestSessionItem();
};

TestSessionItem::~TestSessionItem() = default;

TEST_F(TestSessionItem, initialState)
{
    SessionItem item;
    const int role = ItemDataRole::DATA;

    EXPECT_EQ(item.model(), nullptr);
    EXPECT_EQ(item.parent(), nullptr);
    EXPECT_EQ(item.childrenCount(), 0);
    EXPECT_FALSE(item.data(role).isValid());
    EXPECT_TRUE(item.children().empty());
    EXPECT_TRUE(item.modelType().empty());
    EXPECT_TRUE(item.roles().empty());
}

TEST_F(TestSessionItem, modelType)
{
    SessionItem item2("Layer");
    EXPECT_EQ(item2.modelType(), "Layer");
}

TEST_F(TestSessionItem, setData)
{
    SessionItem item;
    const int role = ItemDataRole::DATA;

    EXPECT_FALSE(item.data(role).isValid());

    QVariant expected(42.0);
    EXPECT_TRUE(item.setData(expected, role));
    EXPECT_EQ(item.roles().size(), 1);
    EXPECT_EQ(item.data(role), expected);

    // setting another value
    EXPECT_TRUE(item.setData(QVariant::fromValue(43.0), role));
    EXPECT_EQ(item.roles().size(), 1);
    EXPECT_EQ(item.data(role), QVariant::fromValue(43.0));
}

//! Attempt to set the different Variant to already existing role.

TEST_F(TestSessionItem, variantMismatch)
{
    SessionItem item;
    const int role = ItemDataRole::DATA;
    QVariant expected(42.0);

    // setting data for the first time
    EXPECT_TRUE(item.setData(expected, role));
    EXPECT_EQ(item.roles().size(), 1);
    EXPECT_EQ(item.data(role), expected);

    // attempt to rewrite variant with another type
    EXPECT_THROW(item.setData(QVariant::fromValue(std::string("abc")), role), std::runtime_error);

    // removing value by passing invalid variant
    EXPECT_NO_THROW(item.setData(QVariant(), role));
    EXPECT_EQ(item.roles().size(), 0);
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

TEST_F(TestSessionItem, takeItem)
{
    std::unique_ptr<SessionItem> parent(new SessionItem);
    auto child1 = new SessionItem;
    auto child2 = new SessionItem;
    auto child3 = new SessionItem;

    // inserting items
    parent->insertItem(-1, child1);
    parent->insertItem(-1, child2);
    parent->insertItem(-1, child3);

    EXPECT_EQ(parent->childrenCount(), 3);

    // taking non-existing rows
    EXPECT_THROW(parent->takeItem(-1), std::runtime_error);
    EXPECT_THROW(parent->takeItem(parent->childrenCount()), std::runtime_error);

    // taking first row
    auto taken = parent->takeItem(0);
    EXPECT_EQ(taken->parent(), nullptr);
    std::vector<SessionItem*> expected = {child2, child3};
    EXPECT_EQ(parent->children(), expected);

    delete taken;
}

//! Item registration in a pool.

TEST_F(TestSessionItem, registerItem)
{
    std::unique_ptr<SessionItem> item(new SessionItem);
    std::shared_ptr<ItemPool> pool;

    EXPECT_TRUE(item->roles().empty());

    // registering item on unexisting pool
    item->register_item(pool);
    EXPECT_TRUE(item->roles().empty());

    // creating pool
    pool.reset(new ItemPool);
    item->register_item(pool);
    auto key = pool->key_for_item(item.get());
    std::vector<int> expected_roles = {ItemDataRole::IDENTIFIER};
    EXPECT_EQ(item->roles(), expected_roles);
    EXPECT_EQ(item->data(ItemDataRole::IDENTIFIER).value<std::string>(), key);
}

//! Item registration in a pool.

TEST_F(TestSessionItem, defaultTag)
{
    SessionItem item;
    EXPECT_EQ(item.defaultTag(), std::string("defaultTag"));
    EXPECT_TRUE(item.isTag("defaultTag"));
}

//! Registering tags

TEST_F(TestSessionItem, registerTag)
{
    SessionItem item;
    item.registerTag(TagInfo::universalTag("tagname"));
    EXPECT_TRUE(item.isTag("tagname"));

    //registering of tag with same name forbidden
    EXPECT_THROW(item.registerTag(TagInfo::universalTag("tagname")), std::runtime_error);

    //registering empty tag is forbidden
    EXPECT_THROW(item.registerTag(TagInfo::universalTag("")), std::runtime_error);

}

//! Insert and take tagged items.

TEST_F(TestSessionItem, singleTagAndItems)
{
    const std::string tag1 = "tag1";

    // creating parent with one tag
    std::unique_ptr<SessionItem> parent(new SessionItem);
    parent->registerTag(TagInfo::universalTag(tag1));
    EXPECT_TRUE(parent->isTag(tag1));

    // inserting two children
    auto child1 = new SessionItem;
    auto child2 = new SessionItem;
    parent->insertItem(-1, child1, tag1);
    parent->insertItem(-1, child2, tag1);

    // testing result of insertion via non-tag interface
    std::vector<SessionItem*> expected = {child1, child2};
    EXPECT_EQ(parent->children(), expected);
    EXPECT_EQ(parent->rowOfChild(child1), 0);
    EXPECT_EQ(parent->rowOfChild(child2), 1);

    // testing single item access via tag interface
    EXPECT_THROW(parent->getItem(), std::runtime_error); // no items in default tag
    EXPECT_EQ(parent->getItem(tag1), child1);
    EXPECT_EQ(parent->getItem(tag1, 0), child1);
    EXPECT_EQ(parent->getItem(tag1, 1), child2);
    EXPECT_THROW(parent->getItem(tag1, 2), std::runtime_error); // wrong row

    // access to multiple items via tags interface
    EXPECT_EQ(parent->getItems(), std::vector<SessionItem*>()); // no items in default tag
    EXPECT_EQ(parent->getItems(tag1), expected);

    // removing first item
    delete parent->takeItem(0, tag1);
    EXPECT_EQ(parent->getItems(tag1), std::vector<SessionItem*>() = {child2});
    // removing second item
    delete parent->takeItem(0, tag1);
    EXPECT_EQ(parent->getItems(tag1), std::vector<SessionItem*>() = {});

    // removing from already empty container
    EXPECT_THROW(parent->takeItem(0, tag1), std::runtime_error);
}

//! Insert and take tagged items when two tags are present.

TEST_F(TestSessionItem, twoTagsAndItems)
{
    const std::string tag1 = "tag1";
    const std::string tag2 = "tag2";

    // creating parent with one tag
    std::unique_ptr<SessionItem> parent(new SessionItem);
    parent->registerTag(TagInfo::universalTag(tag1));
    parent->registerTag(TagInfo::universalTag(tag2));
    EXPECT_TRUE(parent->isTag(tag1));
    EXPECT_TRUE(parent->isTag(tag2));

    // inserting two children
    auto child_t1_a = new SessionItem;
    auto child_t1_b = new SessionItem;
    auto child_t2_a = new SessionItem;
    auto child_t2_b = new SessionItem;
    auto child_t2_c = new SessionItem;
    parent->insertItem(-1, child_t2_a, tag2);
    parent->insertItem(-1, child_t2_c, tag2);

    parent->insertItem(-1, child_t1_a, tag1);
    parent->insertItem(-1, child_t1_b, tag1);

    parent->insertItem(1, child_t2_b, tag2); // between child_t2_a and child_t2_c

    // testing item access via non-tag interface
    std::vector<SessionItem*> expected = {child_t1_a, child_t1_b, child_t2_a, child_t2_b, child_t2_c};
    EXPECT_EQ(parent->children(), expected);
    EXPECT_EQ(parent->rowOfChild(child_t1_a), 0);
    EXPECT_EQ(parent->rowOfChild(child_t2_c), 4);

    // testing single item access via tag interface
    EXPECT_THROW(parent->getItem(), std::runtime_error); // no items in default tag
    EXPECT_EQ(parent->getItem(tag1), child_t1_a);
    EXPECT_EQ(parent->getItem(tag1, 0), child_t1_a);
    EXPECT_EQ(parent->getItem(tag1, 1), child_t1_b);
    EXPECT_EQ(parent->getItem(tag2, 0), child_t2_a);
    EXPECT_EQ(parent->getItem(tag2, 1), child_t2_b);
    EXPECT_EQ(parent->getItem(tag2, 2), child_t2_c);
    EXPECT_THROW(parent->getItem(tag2, 3), std::runtime_error); // no items with such row

    // access to multiple items via tags interface
    EXPECT_EQ(parent->getItems(), std::vector<SessionItem*>()); // no items in default tag
    expected = {child_t1_a, child_t1_b};
    EXPECT_EQ(parent->getItems(tag1), expected);
    expected = {child_t2_a, child_t2_b, child_t2_c};
    EXPECT_EQ(parent->getItems(tag2), expected);

    // removing item from the middle of tag2
    delete parent->takeItem(1, tag2);
    expected = {child_t1_a, child_t1_b};
    EXPECT_EQ(parent->getItems(tag1), expected);
    expected = {child_t2_a, child_t2_c};
    EXPECT_EQ(parent->getItems(tag2), expected);
}

//! Inserting and removing items when tag has limits.

TEST_F(TestSessionItem, tagWithLimits)
{
    const std::string tag1 = "tag1";
    const int maxItems = 3;
    std::unique_ptr<SessionItem> parent(new SessionItem);
    parent->registerTag(TagInfo(tag1, 0, maxItems, std::vector<std::string>() = {}));

    // placing maximu allowed number of items
    std::vector<SessionItem*> expected;
    for (int i = 0; i < maxItems; ++i) {
        auto child = new SessionItem;
        expected.push_back(child);
        EXPECT_TRUE(parent->insertItem(-1, child, tag1));
    }
    EXPECT_EQ(parent->getItems(tag1), expected);

    // no room for extra item
    auto extra = new SessionItem;
    EXPECT_THROW(parent->insertItem(-1, extra, tag1), std::runtime_error);

    // removing first element
    delete parent->takeItem(0, tag1);
    expected.erase(expected.begin());
    EXPECT_EQ(parent->getItems(tag1), expected);

    // adding extra item
    parent->insertItem(-1, extra, tag1);
    expected.push_back(extra);
    EXPECT_EQ(parent->getItems(tag1), expected);
}

//! Inserting and removing items when tag has limits.

TEST_F(TestSessionItem, tagModelTypes)
{
    const std::string tag1 = "tag1";
    const std::string tag2 = "tag2";
    const std::string modelType1 = "ModelType1";
    const std::string modelType2 = "ModelType2";
    const std::string modelType3 = "ModelType3";
    const std::string modelType4 = "ModelType4";

    std::unique_ptr<SessionItem> parent(new SessionItem("ModelType"));
    parent->registerTag(TagInfo(tag1, 0, -1, std::vector<std::string>() = {modelType1, modelType2}));
    parent->registerTag(TagInfo(tag2, 0, -1, std::vector<std::string>() = {modelType3}));

    auto item1 = new SessionItem(modelType1);
    auto item2 = new SessionItem(modelType2);
    auto item3 = new SessionItem(modelType3);

    // attempt to add item not intended for tag
    EXPECT_THROW(parent->insertItem(-1, item1, tag2), std::runtime_error);
    EXPECT_THROW(parent->insertItem(-1, item3, tag1), std::runtime_error);

    // normal insert to appropriate tag
    parent->insertItem(-1, item3, tag2);
    parent->insertItem(-1, item1, tag1);
    parent->insertItem(-1, item2, tag1);

    std::vector<SessionItem*> expected = {item1, item2};
    EXPECT_EQ(parent->getItems(tag1), expected);
    expected = {item3};
    EXPECT_EQ(parent->getItems(tag2), expected);
}

TEST_F(TestSessionItem, tagFromItem)
{
    const std::string tag1 = "tag1";
    const std::string tag2 = "tag2";

    // creating parent with one tag
    std::unique_ptr<SessionItem> parent(new SessionItem);
    parent->registerTag(TagInfo::universalTag(tag1));
    parent->registerTag(TagInfo::universalTag(tag2));

    // inserting two children
    auto child_t1_a = new SessionItem;
    auto child_t1_b = new SessionItem;
    auto child_t2_a = new SessionItem;
    auto child_t2_b = new SessionItem;
    auto child_t2_c = new SessionItem;
    parent->insertItem(-1, child_t2_a, tag2);
    parent->insertItem(-1, child_t2_c, tag2);
    parent->insertItem(-1, child_t1_a, tag1);
    parent->insertItem(-1, child_t1_b, tag1);
    parent->insertItem(1, child_t2_b, tag2); // between child_t2_a and child_t2_c

    EXPECT_EQ(parent->tagFromItem(child_t1_a), "tag1");
    EXPECT_EQ(parent->tagFromItem(child_t1_b), "tag1");
    EXPECT_EQ(parent->tagFromItem(child_t2_a), "tag2");
    EXPECT_EQ(parent->tagFromItem(child_t2_b), "tag2");
    EXPECT_EQ(parent->tagFromItem(child_t2_c), "tag2");

    auto child = new SessionItem;
    EXPECT_EQ(parent->tagFromItem(child), "");
    delete child;
}

