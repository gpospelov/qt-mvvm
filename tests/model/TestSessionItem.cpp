#include "google_test.h"
#include "test_utils.h"
#include "sessionitem.h"
#include "itempool.h"
#include "taginfo.h"
#include "itemutils.h"
#include <memory>
#include <QDebug>

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
    EXPECT_EQ(item.modelType(), Constants::BaseType);
    EXPECT_EQ(item.displayName(), Constants::BaseType);

    // Initially item has already an identifier defined.
    std::vector<int> expected_roles = {ItemDataRole::IDENTIFIER, ItemDataRole::DISPLAY};
    EXPECT_EQ(item.roles(), expected_roles);

    // Identifier is not zero
    EXPECT_FALSE(item.identifier().empty());
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

    std::vector<int> expected_roles = {ItemDataRole::IDENTIFIER, ItemDataRole::DISPLAY, ItemDataRole::DATA};
    EXPECT_EQ(item.roles(), expected_roles);
    EXPECT_EQ(item.data(role), expected);

    // setting another value
    EXPECT_TRUE(item.setData(QVariant::fromValue(43.0), role));
    EXPECT_EQ(item.roles(), expected_roles);
    EXPECT_EQ(item.data(role), QVariant::fromValue(43.0));

    // setting same value
    EXPECT_FALSE(item.setData(QVariant::fromValue(43.0), role));
    EXPECT_EQ(item.roles(), expected_roles);
    EXPECT_EQ(item.data(role), QVariant::fromValue(43.0));
}

//! Display role.

TEST_F(TestSessionItem, displayName)
{
    SessionItem item("Property");
    QVariant data(42.0);
    EXPECT_TRUE(item.setData(data));

    // default display name coincide with model type
    EXPECT_EQ(item.displayName(), "Property");

    // checking setter
    item.setDisplayName("width");
    EXPECT_EQ(item.displayName(), "width");
    EXPECT_EQ(item.data().toDouble(), 42.0);
}

//! Attempt to set the different Variant to already existing role.

TEST_F(TestSessionItem, variantMismatch)
{
    SessionItem item;
    const int role = ItemDataRole::DATA;
    QVariant expected(42.0);

    // setting data for the first time
    EXPECT_TRUE(item.setData(expected, role));

    std::vector<int> expected_roles = {ItemDataRole::IDENTIFIER, ItemDataRole::DISPLAY, ItemDataRole::DATA};
    EXPECT_EQ(item.roles(), expected_roles);
    EXPECT_EQ(item.data(role), expected);

    // attempt to rewrite variant with another type
    EXPECT_THROW(item.setData(QVariant::fromValue(std::string("abc")), role), std::runtime_error);

    // removing value by passing invalid variant
    EXPECT_NO_THROW(item.setData(QVariant(), role));
    EXPECT_EQ(item.roles().size(), 2);
}

//! Item registration in a pool.

TEST_F(TestSessionItem, registerItem)
{
    std::unique_ptr<SessionItem> item(new SessionItem);
    auto item_id = item->identifier();
    EXPECT_EQ(item->roles().size(), 2u);

    std::shared_ptr<ItemPool> pool;

    // creating pool
    pool.reset(new ItemPool);
    pool->register_item(item.get(), item_id);
    // registration shouldn't change item identifier
    EXPECT_EQ(item->identifier(), item_id);

    // registration key should coincide with item identifier
    auto key = pool->key_for_item(item.get());
    std::vector<int> expected_roles = {ItemDataRole::IDENTIFIER, ItemDataRole::DISPLAY};
    EXPECT_EQ(item->roles(), expected_roles);
    EXPECT_EQ(item_id, key);
}

//! Item registration in a pool.

TEST_F(TestSessionItem, defaultTag)
{
    SessionItem item;
    EXPECT_EQ(item.defaultTag(), std::string());
    EXPECT_FALSE(item.isTag("defaultTag"));
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

//! Registering tag and setting it as default

TEST_F(TestSessionItem, registerDefaultTag)
{
    SessionItem item;
    item.registerTag(TagInfo::universalTag("tagname"), /*set_as_default*/true);
    EXPECT_EQ(item.defaultTag(), "tagname");
}

//! Simple child insert.

TEST_F(TestSessionItem, insertItem)
{
    std::unique_ptr<SessionItem> parent(new SessionItem);
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/true);

    std::unique_ptr<SessionItem> child(new SessionItem);

    // empty parent
    EXPECT_EQ(parent->childrenCount(), 0);
    EXPECT_EQ(Utils::IndexOfChild(parent.get(), nullptr), -1);
    EXPECT_EQ(Utils::IndexOfChild(parent.get(), child.get()), -1);
    EXPECT_EQ(parent->getItem("", 0), nullptr);
    EXPECT_EQ(parent->getItem("", -1), nullptr);
    EXPECT_EQ(parent->getItem("", 10), nullptr);

    // inserting child
    auto p_child = child.release();
    parent->insertItem(p_child, "", 0);
    EXPECT_EQ(parent->childrenCount(), 1);
    EXPECT_EQ(Utils::IndexOfChild(parent.get(), p_child), 0);
    EXPECT_EQ(parent->children()[0], p_child);
    EXPECT_EQ(parent->getItem("", 0), p_child);
    EXPECT_EQ(p_child->parent(), parent.get());
}

//! Simple children insert.

TEST_F(TestSessionItem, insertChildren)
{
    std::unique_ptr<SessionItem> parent(new SessionItem);
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/true);

    auto child1 = new SessionItem;
    auto child2 = new SessionItem;
    auto child3 = new SessionItem;
    auto child4 = new SessionItem;

    // inserting two items
    parent->insertItem(child1);
    parent->insertItem(child2);
    EXPECT_EQ(Utils::IndexOfChild(parent.get(), child1), 0);
    EXPECT_EQ(Utils::IndexOfChild(parent.get(), child2), 1);
    EXPECT_EQ(parent->getItem("", 0), child1);
    EXPECT_EQ(parent->getItem("", 1), child2);
    std::vector<SessionItem*> expected = {child1, child2};
    EXPECT_EQ(parent->children(), expected);

    // inserting third item between two others
    parent->insertItem(child3, "", 1);
    expected = {child1, child3, child2};
    EXPECT_EQ(parent->children(), expected);
    EXPECT_EQ(Utils::IndexOfChild(parent.get(), child1), 0);
    EXPECT_EQ(Utils::IndexOfChild(parent.get(), child2), 2);
    EXPECT_EQ(Utils::IndexOfChild(parent.get(), child3), 1);
    EXPECT_EQ(parent->getItem("", 0), child1);
    EXPECT_EQ(parent->getItem("", 1), child3);
    EXPECT_EQ(parent->getItem("", 2), child2);
    EXPECT_EQ(parent->getItem("", 3), nullptr);

    // inserting forth item using index equal to number of items
    parent->insertItem(child4, "", parent->childrenCount());

    // checking parents
    EXPECT_EQ(child1->parent(), parent.get());
    EXPECT_EQ(child2->parent(), parent.get());
    EXPECT_EQ(child3->parent(), parent.get());
    EXPECT_EQ(child4->parent(), parent.get());

    // attempt to insert same item twice
    EXPECT_THROW(parent->insertItem(child2, "", -1), std::runtime_error);

    // attempt to insert item using out of scope index
    auto child5 = std::make_unique<SessionItem>();
    EXPECT_FALSE(parent->insertItem(child5.get(), "",  parent->childrenCount()+1));
}

//! Removing (taking) item from parent.

TEST_F(TestSessionItem, takeItem)
{
    std::unique_ptr<SessionItem> parent(new SessionItem);
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/true);

    auto child1 = new SessionItem;
    auto child2 = new SessionItem;
    auto child3 = new SessionItem;

    // inserting items
    parent->insertItem(child1);
    parent->insertItem(child2);
    parent->insertItem(child3);

    EXPECT_EQ(parent->childrenCount(), 3);

    // taking non-existing rows
    EXPECT_EQ(parent->takeItem("", -1), nullptr);
    EXPECT_EQ(parent->takeItem("", parent->childrenCount()), nullptr);

    // taking first row
    auto taken = parent->takeItem("", 0);
    EXPECT_EQ(taken->parent(), nullptr);
    std::vector<SessionItem*> expected = {child2, child3};
    EXPECT_EQ(parent->children(), expected);

    delete taken;
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
    parent->insertItem(child1, tag1);
    parent->insertItem(child2, tag1);

    // testing result of insertion via non-tag interface
    std::vector<SessionItem*> expected = {child1, child2};
    EXPECT_EQ(parent->children(), expected);
    EXPECT_EQ(Utils::IndexOfChild(parent.get(), child1), 0);
    EXPECT_EQ(Utils::IndexOfChild(parent.get(), child2), 1);

    // testing single item access via tag interface
    EXPECT_EQ(parent->getItem(tag1), child1);
    EXPECT_EQ(parent->getItem(tag1, 0), child1);
    EXPECT_EQ(parent->getItem(tag1, 1), child2);
    EXPECT_EQ(parent->getItem(tag1, 2), nullptr); // wrong row

    // access to multiple items via tags interface
    EXPECT_THROW(parent->getItems(), std::runtime_error); // no default tag registered
    EXPECT_EQ(parent->getItems(tag1), expected);

    // removing first item
    delete parent->takeItem(tag1, 0);
    EXPECT_EQ(parent->getItems(tag1), std::vector<SessionItem*>() = {child2});
    // removing second item
    delete parent->takeItem(tag1, 0);
    EXPECT_EQ(parent->getItems(tag1), std::vector<SessionItem*>() = {});

    // removing from already empty container
    EXPECT_EQ(parent->takeItem(tag1, 0), nullptr);
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
    parent->insertItem(child_t2_a, tag2);
    parent->insertItem(child_t2_c, tag2);

    parent->insertItem(child_t1_a, tag1);
    parent->insertItem(child_t1_b, tag1);

    parent->insertItem(child_t2_b, tag2, 1); // between child_t2_a and child_t2_c

    // testing item access via non-tag interface
    std::vector<SessionItem*> expected = {child_t1_a, child_t1_b, child_t2_a, child_t2_b, child_t2_c};
    EXPECT_EQ(parent->children(), expected);
    EXPECT_EQ(Utils::IndexOfChild(parent.get(), child_t1_a), 0);
    EXPECT_EQ(Utils::IndexOfChild(parent.get(), child_t2_c), 4);

    // testing single item access via tag interface
    EXPECT_EQ(parent->getItem(tag1), child_t1_a);
    EXPECT_EQ(parent->getItem(tag1, 0), child_t1_a);
    EXPECT_EQ(parent->getItem(tag1, 1), child_t1_b);
    EXPECT_EQ(parent->getItem(tag2, 0), child_t2_a);
    EXPECT_EQ(parent->getItem(tag2, 1), child_t2_b);
    EXPECT_EQ(parent->getItem(tag2, 2), child_t2_c);
    EXPECT_EQ(parent->getItem(tag2, 3), nullptr); // no items with such row

    // access to multiple items via tags interface
    EXPECT_THROW(parent->getItems(), std::runtime_error); // no default tag registered
    expected = {child_t1_a, child_t1_b};
    EXPECT_EQ(parent->getItems(tag1), expected);
    expected = {child_t2_a, child_t2_b, child_t2_c};
    EXPECT_EQ(parent->getItems(tag2), expected);

    // removing item from the middle of tag2
    delete parent->takeItem(tag2, 1);
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
        EXPECT_TRUE(parent->insertItem(child, tag1));
    }
    EXPECT_EQ(parent->getItems(tag1), expected);

    // no room for extra item
    auto extra = new SessionItem;
    EXPECT_FALSE(parent->insertItem(extra, tag1));

    // removing first element
    delete parent->takeItem(tag1, 0);
    expected.erase(expected.begin());
    EXPECT_EQ(parent->getItems(tag1), expected);

    // adding extra item
    parent->insertItem(extra, tag1);
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
    EXPECT_FALSE(parent->insertItem(item1, tag2));
    EXPECT_FALSE(parent->insertItem(item3, tag1));

    // normal insert to appropriate tag
    parent->insertItem(item3, tag2);
    parent->insertItem(item1, tag1);
    parent->insertItem(item2, tag1);

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
    parent->insertItem(child_t2_a, tag2);
    parent->insertItem(child_t2_c, tag2);
    parent->insertItem(child_t1_a, tag1);
    parent->insertItem(child_t1_b, tag1);
    parent->insertItem(child_t2_b, tag2, 1); // between child_t2_a and child_t2_c

    EXPECT_EQ(parent->tagFromItem(child_t1_a), "tag1");
    EXPECT_EQ(parent->tagFromItem(child_t1_b), "tag1");
    EXPECT_EQ(parent->tagFromItem(child_t2_a), "tag2");
    EXPECT_EQ(parent->tagFromItem(child_t2_b), "tag2");
    EXPECT_EQ(parent->tagFromItem(child_t2_c), "tag2");

    auto child = new SessionItem;
    EXPECT_EQ(parent->tagFromItem(child), "");
    delete child;
}

//! Checks row of item in its tag

TEST_F(TestSessionItem, tagRowFromItem)
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
    parent->insertItem(child_t2_a, tag2); // 0
    parent->insertItem(child_t2_c, tag2); // 2
    parent->insertItem(child_t1_a, tag1); // 0
    parent->insertItem(child_t1_b, tag1); // 1
    parent->insertItem(child_t2_b, tag2, 1); // 1 between child_t2_a and child_t2_c

    EXPECT_EQ(parent->tagRowOfItem(child_t1_a).row, 0);
    EXPECT_EQ(parent->tagRowOfItem(child_t1_b).row, 1);
    EXPECT_EQ(parent->tagRowOfItem(child_t2_a).row, 0);
    EXPECT_EQ(parent->tagRowOfItem(child_t2_b).row, 1);
    EXPECT_EQ(parent->tagRowOfItem(child_t2_c).row, 2);

    EXPECT_EQ(parent->tagRowOfItem(child_t1_a).tag, "tag1");
    EXPECT_EQ(parent->tagRowOfItem(child_t1_b).tag, "tag1");
    EXPECT_EQ(parent->tagRowOfItem(child_t2_a).tag, "tag2");
    EXPECT_EQ(parent->tagRowOfItem(child_t2_b).tag, "tag2");
    EXPECT_EQ(parent->tagRowOfItem(child_t2_c).tag, "tag2");
}

//! Checks item appearance (enabled/disabled and editable/readonly).

TEST_F(TestSessionItem, appearance)
{
    SessionItem item("Model");

    // there shouldn't be any data
    auto variant = item.data(ItemDataRole::APPEARANCE);
    EXPECT_FALSE(variant.isValid());

    // default status
    EXPECT_TRUE(item.isEnabled());
    EXPECT_TRUE(item.isEditable());

    // disabling item
    item.setEnabled(false);
    EXPECT_FALSE(item.isEnabled());
    EXPECT_TRUE(item.isEditable());

    // data should be there now
    variant = item.data(ItemDataRole::APPEARANCE);
    EXPECT_TRUE(variant.isValid());

    // making it readonly
    item.setEditable(false);
    EXPECT_FALSE(item.isEnabled());
    EXPECT_FALSE(item.isEditable());
}


TEST_F(TestSessionItem, itemsInTag)
{
    const std::string tag1 = "tag1";
    const std::string tag2 = "tag2";

    // creating parent with one tag
    std::unique_ptr<SessionItem> parent(new SessionItem);
    parent->registerTag(TagInfo::universalTag(tag1));
    parent->registerTag(TagInfo::universalTag(tag2));

    // inserting two children
    auto child_t1_a = new SessionItem;
    auto child_t2_a = new SessionItem;
    auto child_t2_b = new SessionItem;
    parent->insertItem(child_t1_a, tag1);
    parent->insertItem(child_t2_a, tag2);
    parent->insertItem(child_t2_b, tag2);

    EXPECT_EQ(parent->itemCount(tag1), 1);
    EXPECT_EQ(parent->itemCount(tag2), 2);
}
