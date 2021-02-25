// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/model/sessionitem.h"

#include "google_test.h"
#include "mvvm/model/itempool.h"
#include "mvvm/model/itemutils.h"
#include "mvvm/model/propertyitem.h"
#include "mvvm/model/sessionitemdata.h"
#include "mvvm/model/sessionitemtags.h"
#include "mvvm/model/taginfo.h"
#include "mvvm/model/variant_constants.h"
#include <memory>
#include <stdexcept>

using namespace ModelView;

class SessionItemTest : public ::testing::Test {
};

TEST_F(SessionItemTest, initialState)
{
    SessionItem item;
    const int role = ItemDataRole::DATA;

    EXPECT_EQ(item.model(), nullptr);
    EXPECT_EQ(item.parent(), nullptr);
    EXPECT_EQ(item.childrenCount(), 0);
    EXPECT_FALSE(item.data<QVariant>(role).isValid());
    EXPECT_TRUE(item.children().empty());
    EXPECT_EQ(item.modelType(), Constants::BaseType);
    EXPECT_EQ(item.displayName(), Constants::BaseType);

    // Initially item has already an identifier defined.
    std::vector<int> expected_roles = {ItemDataRole::IDENTIFIER, ItemDataRole::DISPLAY};
    EXPECT_EQ(item.itemData()->roles(), expected_roles);

    // Identifier is not zero
    EXPECT_FALSE(item.identifier().empty());
}

TEST_F(SessionItemTest, modelType)
{
    SessionItem item2("Layer");
    EXPECT_EQ(item2.modelType(), "Layer");
}

//! Validating ::setData and appearance of roles.

TEST_F(SessionItemTest, setData)
{
    SessionItem item;
    const int role = ItemDataRole::DATA;

    EXPECT_FALSE(item.data<QVariant>(role).isValid());

    QVariant expected(42.0);
    EXPECT_TRUE(item.setData(expected, role));

    std::vector<int> expected_roles = {ItemDataRole::IDENTIFIER, ItemDataRole::DISPLAY,
                                       ItemDataRole::DATA};
    EXPECT_EQ(item.itemData()->roles(), expected_roles);
    EXPECT_EQ(item.data<QVariant>(role), expected);

    // setting another value
    EXPECT_TRUE(item.setData(43.0, role));
    EXPECT_EQ(item.itemData()->roles(), expected_roles);
    EXPECT_EQ(item.data<QVariant>(role), QVariant::fromValue(43.0));

    // setting same value
    EXPECT_FALSE(item.setData(43.0, role));
    EXPECT_EQ(item.itemData()->roles(), expected_roles);
    EXPECT_EQ(item.data<QVariant>(role), QVariant::fromValue(43.0));
}

//! Validating ::setData in the context of implicit conversion.

TEST_F(SessionItemTest, setDataAndImplicitConversion)
{
    {
        SessionItem item;
        const int role = ItemDataRole::DATA;
        EXPECT_TRUE(item.setData(43.0, ItemDataRole::DATA));
        EXPECT_EQ(item.data<QVariant>(role).typeName(), Constants::double_type_name);
    }

    {
        SessionItem item;
        const int role = ItemDataRole::DATA;
        EXPECT_TRUE(item.setData(43, ItemDataRole::DATA));
        EXPECT_EQ(item.data<QVariant>(role).typeName(), Constants::int_type_name);
    }
}

TEST_F(SessionItemTest, hasData)
{
    SessionItem item;

    EXPECT_FALSE(item.hasData());
    EXPECT_TRUE(item.hasData(ItemDataRole::IDENTIFIER));
    EXPECT_FALSE(item.hasData(ItemDataRole::DATA));
    EXPECT_TRUE(item.hasData(ItemDataRole::DISPLAY));
    EXPECT_FALSE(item.hasData(ItemDataRole::APPEARANCE));
    EXPECT_FALSE(item.hasData(ItemDataRole::LIMITS));
    EXPECT_FALSE(item.hasData(ItemDataRole::TOOLTIP));
    EXPECT_FALSE(item.hasData(ItemDataRole::EDITORTYPE));

    item.setData(42.0);
    EXPECT_TRUE(item.hasData());
}

TEST_F(SessionItemTest, setDoubleData)
{
    SessionItem item;
    const double expected = 42.0;
    EXPECT_TRUE(item.setData(expected));
    EXPECT_EQ(item.data<double>(), expected);
}

TEST_F(SessionItemTest, setIntData)
{
    SessionItem item;
    const int expected = 42;
    EXPECT_TRUE(item.setData(expected));
    EXPECT_EQ(item.data<int>(), expected);
}

TEST_F(SessionItemTest, setBoolData)
{
    SessionItem item;
    const bool expected_true = true;
    EXPECT_TRUE(item.setData(expected_true));
    EXPECT_EQ(item.data<bool>(), expected_true);
    const bool expected_false = false;
    EXPECT_TRUE(item.setData(expected_false));
    EXPECT_EQ(item.data<bool>(), expected_false);
}

TEST_F(SessionItemTest, setStringData)
{
    SessionItem item;
    const std::string expected{"abc"};
    EXPECT_TRUE(item.setData(expected));
    EXPECT_EQ(item.data<std::string>(), expected);
}

//! Display role.

TEST_F(SessionItemTest, displayName)
{
    SessionItem item("Property");
    QVariant data(42.0);
    EXPECT_TRUE(item.setData(data));

    // default display name coincide with model type
    EXPECT_EQ(item.displayName(), "Property");

    // checking setter
    item.setDisplayName("width");
    EXPECT_EQ(item.displayName(), "width");
    EXPECT_EQ(item.data<double>(), 42.0);
}

//! Attempt to set the different Variant to already existing role.

TEST_F(SessionItemTest, variantMismatch)
{
    SessionItem item;
    const int role = ItemDataRole::DATA;
    QVariant expected(42.0);

    // setting data for the first time
    EXPECT_TRUE(item.setData(expected, role));

    std::vector<int> expected_roles = {ItemDataRole::IDENTIFIER, ItemDataRole::DISPLAY,
                                       ItemDataRole::DATA};
    EXPECT_EQ(item.itemData()->roles(), expected_roles);
    EXPECT_EQ(item.data<QVariant>(role), expected);

    // attempt to rewrite variant with another type
    EXPECT_THROW(item.setData(std::string("abc"), role), std::runtime_error);

    // removing value by passing invalid variant
    EXPECT_NO_THROW(item.setData(QVariant(), role));
    EXPECT_EQ(item.itemData()->roles().size(), 2);
}

//! Item registration in a pool.

TEST_F(SessionItemTest, registerItem)
{
    auto item = std::make_unique<SessionItem>();
    auto item_id = item->identifier();
    EXPECT_EQ(item->itemData()->roles().size(), 2u);

    std::shared_ptr<ItemPool> pool;

    // creating pool
    pool.reset(new ItemPool);
    pool->register_item(item.get(), item_id);
    // registration shouldn't change item identifier
    EXPECT_EQ(item->identifier(), item_id);

    // registration key should coincide with item identifier
    auto key = pool->key_for_item(item.get());
    std::vector<int> expected_roles = {ItemDataRole::IDENTIFIER, ItemDataRole::DISPLAY};
    EXPECT_EQ(item->itemData()->roles(), expected_roles);
    EXPECT_EQ(item_id, key);
}

//! Item registration in a pool.

TEST_F(SessionItemTest, defaultTag)
{
    SessionItem item;
    EXPECT_EQ(item.itemTags()->defaultTag(), std::string());
    EXPECT_FALSE(Utils::HasTag(item, "defaultTag"));
}

//! Registering tags

TEST_F(SessionItemTest, registerTag)
{
    SessionItem item;
    item.registerTag(TagInfo::universalTag("tagname"));
    EXPECT_TRUE(Utils::HasTag(item, "tagname"));

    // registering of tag with same name forbidden
    EXPECT_THROW(item.registerTag(TagInfo::universalTag("tagname")), std::runtime_error);

    // registering empty tag is forbidden
    EXPECT_THROW(item.registerTag(TagInfo::universalTag("")), std::runtime_error);
}

//! Registering tag and setting it as default

TEST_F(SessionItemTest, registerDefaultTag)
{
    SessionItem item;
    item.registerTag(TagInfo::universalTag("tagname"), /*set_as_default*/ true);
    EXPECT_EQ(item.itemTags()->defaultTag(), "tagname");
}

//! Simple child insert.

TEST_F(SessionItemTest, insertItem)
{
    auto parent = std::make_unique<SessionItem>();
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);

    auto child = std::make_unique<SessionItem>();
    auto p_child = child.get();

    // empty parent
    EXPECT_EQ(parent->childrenCount(), 0);
    EXPECT_EQ(Utils::IndexOfChild(parent.get(), nullptr), -1);
    EXPECT_EQ(Utils::IndexOfChild(parent.get(), child.get()), -1);
    EXPECT_EQ(parent->getItem("", 0), nullptr);
    EXPECT_EQ(parent->getItem("", -1), nullptr);
    EXPECT_EQ(parent->getItem("", 10), nullptr);

    // inserting child
    auto inserted = parent->insertItem(std::move(child), {"", 0});
    EXPECT_EQ(inserted, p_child);
    EXPECT_EQ(parent->childrenCount(), 1);
    EXPECT_EQ(Utils::IndexOfChild(parent.get(), inserted), 0);
    EXPECT_EQ(parent->children()[0], inserted);
    EXPECT_EQ(parent->getItem("", 0), inserted);
    EXPECT_EQ(inserted->parent(), parent.get());
}

//! Simple child insert.

TEST_F(SessionItemTest, insertItemTemplated)
{
    auto parent = std::make_unique<SessionItem>();
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);

    // inserting child
    auto inserted = parent->insertItem({"", 0});
    EXPECT_EQ(parent->childrenCount(), 1);
    EXPECT_EQ(Utils::IndexOfChild(parent.get(), inserted), 0);
    EXPECT_EQ(parent->children()[0], inserted);
    EXPECT_EQ(parent->getItem("", 0), inserted);
    EXPECT_EQ(inserted->parent(), parent.get());

    // inserting property item
    auto property = parent->insertItem<PropertyItem>({"", 1});
    EXPECT_EQ(parent->childrenCount(), 2);
    EXPECT_EQ(Utils::IndexOfChild(parent.get(), property), 1);
    EXPECT_EQ(parent->children()[1], property);
    EXPECT_EQ(parent->getItem("", 1), property);
    EXPECT_EQ(property->parent(), parent.get());
}

//! Simple children insert.

TEST_F(SessionItemTest, insertChildren)
{
    auto parent = std::make_unique<SessionItem>();
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);

    // inserting two items
    auto child1 = parent->insertItem(TagRow::append());
    auto child2 = parent->insertItem(TagRow::append());
    EXPECT_EQ(Utils::IndexOfChild(parent.get(), child1), 0);
    EXPECT_EQ(Utils::IndexOfChild(parent.get(), child2), 1);
    EXPECT_EQ(parent->getItem("", 0), child1);
    EXPECT_EQ(parent->getItem("", 1), child2);
    std::vector<SessionItem*> expected = {child1, child2};
    EXPECT_EQ(parent->children(), expected);

    // inserting third item between two others
    auto child3 = parent->insertItem({"", 1});
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
    auto child4 = parent->insertItem({"", parent->childrenCount()});

    // checking parents
    EXPECT_EQ(child1->parent(), parent.get());
    EXPECT_EQ(child2->parent(), parent.get());
    EXPECT_EQ(child3->parent(), parent.get());
    EXPECT_EQ(child4->parent(), parent.get());

    // attempt to insert item using out of scope index
    auto child5 = std::make_unique<SessionItem>();
    EXPECT_THROW(parent->insertItem(std::move(child5), {"", parent->childrenCount() + 1}),
                 std::runtime_error);
}

//! Removing (taking) item from parent.

TEST_F(SessionItemTest, takeItem)
{
    auto parent = std::make_unique<SessionItem>();
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);

    // inserting items
    parent->insertItem(TagRow::append());
    auto child2 = parent->insertItem(TagRow::append());
    auto child3 = parent->insertItem(TagRow::append());

    EXPECT_EQ(parent->childrenCount(), 3);

    // taking non-existing rows
    EXPECT_EQ(parent->takeItem({"", -1}), nullptr);
    EXPECT_EQ(parent->takeItem({"", parent->childrenCount()}), nullptr);

    // taking first row
    auto taken = parent->takeItem({"", 0});
    EXPECT_EQ(taken->parent(), nullptr);
    std::vector<SessionItem*> expected = {child2, child3};
    EXPECT_EQ(parent->children(), expected);
}

//! Insert and take tagged items.

TEST_F(SessionItemTest, singleTagAndItems)
{
    const std::string tag1 = "tag1";

    // creating parent with one tag
    auto parent = std::make_unique<SessionItem>();
    parent->registerTag(TagInfo::universalTag(tag1));
    EXPECT_TRUE(Utils::HasTag(*parent, tag1));

    // inserting two children
    auto child1 = parent->insertItem({tag1, -1});
    auto child2 = parent->insertItem({tag1, -1});

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
    EXPECT_EQ(parent->getItems(tag1), expected);

    // removing first item
    parent->takeItem({tag1, 0});
    EXPECT_EQ(parent->getItems(tag1), std::vector<SessionItem*>() = {child2});
    // removing second item
    parent->takeItem({tag1, 0});
    EXPECT_EQ(parent->getItems(tag1), std::vector<SessionItem*>() = {});

    // removing from already empty container
    EXPECT_EQ(parent->takeItem({tag1, 0}), nullptr);
}

//! Insert and take tagged items when two tags are present.

TEST_F(SessionItemTest, twoTagsAndItems)
{
    const std::string tag1 = "tag1";
    const std::string tag2 = "tag2";

    // creating parent with one tag
    auto parent = std::make_unique<SessionItem>();
    parent->registerTag(TagInfo::universalTag(tag1));
    parent->registerTag(TagInfo::universalTag(tag2));
    EXPECT_TRUE(Utils::HasTag(*parent, tag1));
    EXPECT_TRUE(Utils::HasTag(*parent, tag2));

    // inserting two children
    auto child_t2_a = parent->insertItem({tag2, -1});
    auto child_t2_c = parent->insertItem({tag2, -1});
    auto child_t1_a = parent->insertItem({tag1, -1});
    auto child_t1_b = parent->insertItem({tag1, -1});
    auto child_t2_b = parent->insertItem({tag2, 1}); // between child_t2_a and child_t2_c

    // testing item access via non-tag interface
    std::vector<SessionItem*> expected = {child_t1_a, child_t1_b, child_t2_a, child_t2_b,
                                          child_t2_c};
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
    expected = {child_t1_a, child_t1_b};
    EXPECT_EQ(parent->getItems(tag1), expected);
    expected = {child_t2_a, child_t2_b, child_t2_c};
    EXPECT_EQ(parent->getItems(tag2), expected);

    // removing item from the middle of tag2
    parent->takeItem({tag2, 1});
    expected = {child_t1_a, child_t1_b};
    EXPECT_EQ(parent->getItems(tag1), expected);
    expected = {child_t2_a, child_t2_c};
    EXPECT_EQ(parent->getItems(tag2), expected);
}

//! Inserting and removing items when tag has limits.

TEST_F(SessionItemTest, tagWithLimits)
{
    const std::string tag1 = "tag1";
    const int maxItems = 3;
    auto parent = std::make_unique<SessionItem>();
    parent->registerTag(TagInfo(tag1, 0, maxItems, std::vector<std::string>() = {}));

    // placing maximu allowed number of items
    std::vector<SessionItem*> expected;
    for (int i = 0; i < maxItems; ++i) {
        auto child = new SessionItem;
        expected.push_back(child);
        EXPECT_TRUE(parent->insertItem(child, {tag1, -1}));
    }
    EXPECT_EQ(parent->getItems(tag1), expected);

    // no room for extra item
    auto extra = new SessionItem;
    EXPECT_FALSE(parent->insertItem(extra, {tag1, -1}));

    // removing first element
    parent->takeItem({tag1, 0});
    expected.erase(expected.begin());
    EXPECT_EQ(parent->getItems(tag1), expected);

    // adding extra item
    parent->insertItem(extra, {tag1, -1});
    expected.push_back(extra);
    EXPECT_EQ(parent->getItems(tag1), expected);
}

//! Inserting and removing items when tag has limits.
TEST_F(SessionItemTest, tagModelTypes)
{
    const std::string tag1 = "tag1";
    const std::string tag2 = "tag2";
    const std::string modelType1 = "ModelType1";
    const std::string modelType2 = "ModelType2";
    const std::string modelType3 = "ModelType3";
    const std::string modelType4 = "ModelType4";

    auto parent = std::make_unique<SessionItem>();
    parent->registerTag(
        TagInfo(tag1, 0, -1, std::vector<std::string>() = {modelType1, modelType2}));
    parent->registerTag(TagInfo(tag2, 0, -1, std::vector<std::string>() = {modelType3}));

    auto item1 = new SessionItem(modelType1);
    auto item2 = new SessionItem(modelType2);
    auto item3 = new SessionItem(modelType3);

    // attempt to add item not intended for tag
    EXPECT_FALSE(parent->insertItem(item1, {tag2, -1}));
    EXPECT_FALSE(parent->insertItem(item3, {tag1, -1}));

    // normal insert to appropriate tag
    parent->insertItem(item3, {tag2, -1});
    parent->insertItem(item1, {tag1, -1});
    parent->insertItem(item2, {tag1, -1});

    std::vector<SessionItem*> expected = {item1, item2};
    EXPECT_EQ(parent->getItems(tag1), expected);
    expected = {item3};
    EXPECT_EQ(parent->getItems(tag2), expected);
}

//! Testing method ::tag.

TEST_F(SessionItemTest, tag)
{
    const std::string tag1 = "tag1";
    const std::string tag2 = "tag2";

    // creating parent with one tag
    auto parent = std::make_unique<SessionItem>();
    parent->registerTag(TagInfo::universalTag(tag1));
    parent->registerTag(TagInfo::universalTag(tag2));

    // inserting two children
    auto child_t2_a = parent->insertItem({tag2, -1});
    auto child_t2_c = parent->insertItem({tag2, -1});
    auto child_t1_a = parent->insertItem({tag1, -1});
    auto child_t1_b = parent->insertItem({tag1, -1});
    auto child_t2_b = parent->insertItem({tag2, 1}); // between child_t2_a and child_t2_c

    EXPECT_EQ(child_t1_a->tagRow().tag, "tag1");
    EXPECT_EQ(child_t1_b->tagRow().tag, "tag1");
    EXPECT_EQ(child_t2_a->tagRow().tag, "tag2");
    EXPECT_EQ(child_t2_b->tagRow().tag, "tag2");
    EXPECT_EQ(child_t2_c->tagRow().tag, "tag2");

    SessionItem parentless_item;
    EXPECT_EQ(parentless_item.tagRow().tag, "");
}

//! Checks row of item in its tag

TEST_F(SessionItemTest, tagRow)
{
    const std::string tag1 = "tag1";
    const std::string tag2 = "tag2";

    // creating parent with one tag
    auto parent = std::make_unique<SessionItem>();
    parent->registerTag(TagInfo::universalTag(tag1));
    parent->registerTag(TagInfo::universalTag(tag2));

    // inserting two children
    auto child_t2_a = parent->insertItem({tag2, -1}); // 0
    auto child_t2_c = parent->insertItem({tag2, -1}); // 2
    auto child_t1_a = parent->insertItem({tag1, -1}); // 0
    auto child_t1_b = parent->insertItem({tag1, -1}); // 1
    auto child_t2_b = parent->insertItem({tag2, 1});  // 1 between child_t2_a and child_t2_c

    EXPECT_EQ(child_t1_a->tagRow().row, 0);
    EXPECT_EQ(child_t1_b->tagRow().row, 1);
    EXPECT_EQ(child_t2_a->tagRow().row, 0);
    EXPECT_EQ(child_t2_b->tagRow().row, 1);
    EXPECT_EQ(child_t2_c->tagRow().row, 2);

    EXPECT_EQ(child_t1_a->tagRow().tag, "tag1");
    EXPECT_EQ(child_t1_b->tagRow().tag, "tag1");
    EXPECT_EQ(child_t2_a->tagRow().tag, "tag2");
    EXPECT_EQ(child_t2_b->tagRow().tag, "tag2");
    EXPECT_EQ(child_t2_c->tagRow().tag, "tag2");
}

//! Checks row of item in its tag

TEST_F(SessionItemTest, tagRowOfItem)
{
    const std::string tag1 = "tag1";
    const std::string tag2 = "tag2";

    // creating parent with one tag
    auto parent = std::make_unique<SessionItem>();
    parent->registerTag(TagInfo::universalTag(tag1));
    parent->registerTag(TagInfo::universalTag(tag2));

    // inserting two children
    auto child_t2_a = parent->insertItem({tag2, -1}); // 0
    auto child_t2_c = parent->insertItem({tag2, -1}); // 2
    auto child_t1_a = parent->insertItem({tag1, -1}); // 0
    auto child_t1_b = parent->insertItem({tag1, -1}); // 1
    auto child_t2_b = parent->insertItem({tag2, 1});  // 1 between child_t2_a and child_t2_c

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

TEST_F(SessionItemTest, appearance)
{
    SessionItem item("Model");

    // there shouldn't be any data
    auto variant = item.data<QVariant>(ItemDataRole::APPEARANCE);
    EXPECT_FALSE(variant.isValid());

    // default status
    EXPECT_TRUE(item.isEnabled());
    EXPECT_TRUE(item.isEditable());
    EXPECT_TRUE(item.isVisible());

    // disabling item
    item.setEnabled(false);
    EXPECT_FALSE(item.isEnabled());
    EXPECT_TRUE(item.isEditable());
    EXPECT_TRUE(item.isVisible());

    // data should be there now
    variant = item.data<QVariant>(ItemDataRole::APPEARANCE);
    EXPECT_TRUE(variant.isValid());

    // making it readonly
    item.setEditable(false);
    EXPECT_FALSE(item.isEnabled());
    EXPECT_FALSE(item.isEditable());
    EXPECT_TRUE(item.isVisible());

    // making it hidden
    item.setVisible(false);
    EXPECT_FALSE(item.isEnabled());
    EXPECT_FALSE(item.isEditable());
    EXPECT_FALSE(item.isVisible());
}

//! Checks item tooltip.

TEST_F(SessionItemTest, tooltip)
{
    SessionItem item("Model");

    EXPECT_EQ(item.toolTip(), "");
    EXPECT_FALSE(item.hasData(ItemDataRole::TOOLTIP));

    EXPECT_EQ(item.setToolTip("abc"), &item);
    EXPECT_TRUE(item.hasData(ItemDataRole::TOOLTIP));
    EXPECT_EQ(item.toolTip(), "abc");
}

//! Checks item's editor type.

TEST_F(SessionItemTest, editorType)
{
    SessionItem item("Model");

    EXPECT_EQ(item.editorType(), "");
    EXPECT_FALSE(item.hasData(ItemDataRole::EDITORTYPE));

    EXPECT_EQ(item.setEditorType("abc"), &item);
    EXPECT_TRUE(item.hasData(ItemDataRole::EDITORTYPE));
    EXPECT_EQ(item.editorType(), "abc");
}

TEST_F(SessionItemTest, itemsInTag)
{
    const std::string tag1 = "tag1";
    const std::string tag2 = "tag2";

    // creating parent with one tag
    auto parent = std::make_unique<SessionItem>();
    parent->registerTag(TagInfo::universalTag(tag1));
    parent->registerTag(TagInfo::universalTag(tag2));

    // inserting two children
    parent->insertItem({tag1, -1});
    parent->insertItem({tag2, -1});
    parent->insertItem({tag2, -1});

    EXPECT_EQ(parent->itemCount(tag1), 1);
    EXPECT_EQ(parent->itemCount(tag2), 2);
}
