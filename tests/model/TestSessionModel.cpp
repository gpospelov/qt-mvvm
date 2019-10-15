#include "google_test.h"
#include "itempool.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "taginfo.h"
#include "itemutils.h"
#include "propertyitem.h"
#include <memory>

using namespace ModelView;

class TestSessionModel : public ::testing::Test
{
public:
    ~TestSessionModel();
};

TestSessionModel::~TestSessionModel() = default;

TEST_F(TestSessionModel, initialState)
{
    SessionModel model;
    EXPECT_EQ(model.rootItem()->model(), &model);
    EXPECT_EQ(model.rootItem()->parent(), nullptr);
}

TEST_F(TestSessionModel, insertItem)
{
    auto pool = std::make_shared<ItemPool>();
    SessionModel model("Test", pool);

    const model_type modelType = Constants::BaseType;

    // inserting single item
    auto item = model.insertItem<SessionItem>();
    EXPECT_TRUE(item != nullptr);
    EXPECT_EQ(item->parent(), model.rootItem());
    EXPECT_EQ(item->model(), &model);
    EXPECT_EQ(item->modelType(), modelType);

    // checking registration
    auto item_key = item->identifier();
    EXPECT_EQ(pool->item_for_key(item_key), item);

    // registering tag
    item->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);

    // adding child to it
    auto child = model.insertItem<SessionItem>(item);
    auto child_key = child->identifier();
    EXPECT_EQ(pool->item_for_key(child_key), child);

    EXPECT_TRUE(child != nullptr);
    EXPECT_EQ(child->parent(), item);
    EXPECT_EQ(child->model(), &model);
    EXPECT_EQ(child->modelType(), modelType);

    // taking child back
    auto taken = item->takeItem({"", 0});
    EXPECT_EQ(taken, child);
    EXPECT_EQ(child->model(), nullptr);

    // childitem not registered anymore
    EXPECT_EQ(pool->item_for_key(child_key), nullptr);

    delete taken;
}


TEST_F(TestSessionModel, insertNewItem)
{
    auto pool = std::make_shared<ItemPool>();
    SessionModel model("Test", pool);

    const model_type modelType = Constants::BaseType;

    // inserting single item
    auto item = model.insertNewItem(modelType);
    EXPECT_TRUE(item != nullptr);
    EXPECT_EQ(item->parent(), model.rootItem());
    EXPECT_EQ(item->model(), &model);
    EXPECT_EQ(item->modelType(), modelType);

    // checking registration
    auto item_key = item->identifier();
    EXPECT_EQ(pool->item_for_key(item_key), item);

    // registering tag
    item->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);

    // adding child to it
    auto child = model.insertNewItem(modelType, item);
    auto child_key = child->identifier();
    EXPECT_EQ(pool->item_for_key(child_key), child);

    EXPECT_TRUE(child != nullptr);
    EXPECT_EQ(child->parent(), item);
    EXPECT_EQ(child->model(), &model);
    EXPECT_EQ(child->modelType(), modelType);

    // taking child back
    auto taken = item->takeItem({"", 0});
    EXPECT_EQ(taken, child);
    EXPECT_EQ(child->model(), nullptr);

    // childitem not registered anymore
    EXPECT_EQ(pool->item_for_key(child_key), nullptr);

    delete taken;
}

TEST_F(TestSessionModel, insertNewItemWithTag)
{
    const std::string tag1("tag1");
    SessionModel model;
    auto parent = model.insertItem<SessionItem>();
    parent->registerTag(TagInfo::universalTag(tag1));
    auto child1 = model.insertItem<PropertyItem>(parent, tag1, -1);

    EXPECT_EQ(parent->tagFromItem(child1), tag1);
    EXPECT_EQ(Utils::IndexOfChild(parent, child1), 0);

    // adding second child
    auto child2 = model.insertItem<PropertyItem>(parent, tag1, 0);

    EXPECT_EQ(parent->tagFromItem(child2), tag1);
    EXPECT_EQ(Utils::IndexOfChild(parent, child1), 1);
    EXPECT_EQ(Utils::IndexOfChild(parent, child2), 0);
}

TEST_F(TestSessionModel, setData)
{
    SessionModel model;

    // inserting single item
    auto item = model.insertItem<SessionItem>();
    EXPECT_TRUE(model.data(item, ItemDataRole::DISPLAY).isValid());

    // setting wrong type of data
    QVariant value(42.0);
    EXPECT_THROW(model.setData(item, value, ItemDataRole::DISPLAY), std::runtime_error);

    // setting new data
    EXPECT_TRUE(model.setData(item, value, ItemDataRole::DATA));
    EXPECT_EQ(model.data(item, ItemDataRole::DATA), value);

    // setting same data twice should return false
    EXPECT_FALSE(model.setData(item, value, ItemDataRole::DATA));
}

TEST_F(TestSessionModel, removeItem)
{
    auto pool = std::make_shared<ItemPool>();
    SessionModel model("Test", pool);

    auto parent = model.insertItem<SessionItem>();
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);

    auto child1 = model.insertItem<SessionItem>(parent);
    auto child2 = model.insertItem<SessionItem>(parent, "", 0); // before child1
    Q_UNUSED(child2)

    // removing child2
    model.removeItem(parent, "", 0); // removing child2
    EXPECT_EQ(parent->childrenCount(), 1);
    EXPECT_EQ(Utils::ChildAt(parent, 0), child1);

    // child2 shouldn't be registered anymore
    EXPECT_EQ(pool->key_for_item(child2), "");
}

TEST_F(TestSessionModel, removeNonExistingItem)
{
    auto pool = std::make_shared<ItemPool>();
    SessionModel model("Test", pool);

    auto parent = model.insertItem<SessionItem>();
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);

    // removing non existing child
    EXPECT_NO_THROW(model.removeItem(parent, "", 0));
}


TEST_F(TestSessionModel, takeRowFromRootItem)
{
    auto pool = std::make_shared<ItemPool>();
    SessionModel model("Test", pool);

    auto parent = model.insertItem<SessionItem>();
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);
    auto parent_key = parent->identifier();

    auto child = model.insertItem<SessionItem>(parent);
    auto child_key = child->identifier();

    EXPECT_EQ(pool->item_for_key(parent_key), parent);
    EXPECT_EQ(pool->item_for_key(child_key), child);

    // taking parent
    auto taken = model.rootItem()->takeItem({"", 0});
    EXPECT_EQ(pool->item_for_key(parent_key), nullptr);
    EXPECT_EQ(pool->item_for_key(child_key), nullptr);
    delete taken;
}

TEST_F(TestSessionModel, moveItem)
{
    SessionModel model;

    // parent with child
    auto parent0 = model.insertItem<SessionItem>();
    parent0->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);
    auto child0 = model.insertItem<PropertyItem>(parent0);

    // another parent with child
    auto parent1 = model.insertItem<SessionItem>();
    parent1->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);
    auto child1 = model.insertItem<PropertyItem>(parent1);

    // moving child0 from parent0 to parent 1
    model.moveItem(child0, parent1, "", 0);

    std::vector<SessionItem*> expected = {child0, child1};
    EXPECT_EQ(parent1->children(), expected);
    EXPECT_EQ(parent0->children().size(), 0);
}

TEST_F(TestSessionModel, clearModel)
{
    auto pool = std::make_shared<ItemPool>();
    SessionModel model("test", pool);

    EXPECT_EQ(pool->size(), 1);

    auto first_root = model.rootItem();

    EXPECT_EQ(model.rootItem()->childrenCount(), 0);
    model.insertItem<SessionItem>();
    model.insertItem<SessionItem>();
    EXPECT_EQ(model.rootItem()->childrenCount(), 2);

    model.clear();
    EXPECT_EQ(model.rootItem()->childrenCount(), 0);
    EXPECT_FALSE(model.rootItem() == first_root);
    EXPECT_EQ(pool->key_for_item(first_root), "");
    EXPECT_EQ(pool->size(), 1);
}

//! Tests item copy when from root item to root item.

TEST_F(TestSessionModel, copyModelItemRootContext)
{
    SessionModel model;

    // create single item with value
    auto item = model.insertItem<SessionItem>();
    item->setData(42.0);

    // copying to root item
    auto copy = model.copyItem(item, model.rootItem());

    // checking copy
    ASSERT_TRUE(copy != nullptr);
    ASSERT_TRUE(copy != item);
    EXPECT_FALSE(copy->identifier().empty());
    EXPECT_TRUE(copy->identifier() != item->identifier());
    EXPECT_EQ(copy->data().toDouble(), 42.0);
    EXPECT_EQ(model.rootItem()->children().size(), 2);
    EXPECT_TRUE(item!=copy);
    std::vector<SessionItem*> expected = {item, copy};
    EXPECT_EQ(model.rootItem()->children(), expected);
}

//! Tests item copy from parent to root item.

TEST_F(TestSessionModel, copyParentWithProperty)
{
    SessionModel model;

    // parent with single child and data on ite
    auto parent0 = model.insertItem<SessionItem>();
    parent0->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);
    auto child0 = model.insertItem<SessionItem>(parent0);
    child0->setData(42.0);

    // copying whole parent to root
    auto copy = model.copyItem(parent0, model.rootItem());
    auto copy_child = copy->getItem("defaultTag");

    ASSERT_TRUE(copy != nullptr);
    ASSERT_TRUE(copy_child != nullptr);
    EXPECT_FALSE(copy->identifier().empty());
    EXPECT_TRUE(copy->identifier() != parent0->identifier());
    EXPECT_EQ(copy_child->data().toDouble(), 42.0);
}

//! Tests item copy for property item.

TEST_F(TestSessionModel, copyFreeItem)
{
    SessionModel model;

    // single parent in a model
    auto parent0 = model.insertItem<SessionItem>();
    parent0->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);

    // free item
    auto item = std::make_unique<PropertyItem>();
    item->setData(42.0);

    // copying to parent
    auto copy = model.copyItem(item.get(), parent0, "", -1);
    EXPECT_EQ(copy->data().toDouble(), 42.0);
}

//! Attempt to copy property item into the same tag.

TEST_F(TestSessionModel, forbiddenCopy)
{
    SessionModel model;

    // single parent in a model
    auto parent0 = model.insertItem<SessionItem>();
    parent0->registerTag(TagInfo::propertyTag("property", "Property"));
    auto property = model.insertItem<PropertyItem>(parent0, "property", -1);

    // copying property to same property tag is not allowed
    auto copy = model.copyItem(property, parent0, "property", -1);
    EXPECT_EQ(parent0->childrenCount(), 1);
    EXPECT_EQ(copy, nullptr);
}

//! Test item find using identifier.

TEST_F(TestSessionModel, findItem)
{
    SessionModel model;
    auto parent = model.insertItem<SessionItem>();

    // check that we can find item using its own identofoer
    const identifier_type id = parent->identifier();
    EXPECT_EQ(model.findItem(id), parent);

    // check that we can't find deleted item.
    model.removeItem(model.rootItem(), "", 0);
    EXPECT_EQ(model.findItem(id), nullptr);
}

//! Test items in different models.

TEST_F(TestSessionModel, findItemInAlienModel)
{
    // two models with common pool
    auto pool = std::make_shared<ItemPool>();
    SessionModel model1("Test1", pool);
    SessionModel model2("Test2", pool);

    // inserting items in both models
    auto parent1 = model1.insertItem<SessionItem>();
    auto parent2 = model2.insertItem<SessionItem>();
    const identifier_type id1 = parent1->identifier();
    const identifier_type id2 = parent2->identifier();

    // checking that we can access items from both models
    EXPECT_EQ(model1.findItem(id1), parent1);
    EXPECT_EQ(model2.findItem(id1), parent1);
    EXPECT_EQ(model1.findItem(id2), parent2);
    EXPECT_EQ(model2.findItem(id2), parent2);

    // check that we can't find deleted item.
    model1.removeItem(model1.rootItem(), "", 0);
    EXPECT_EQ(model1.findItem(id1), nullptr);
    EXPECT_EQ(model2.findItem(id1), nullptr);
    EXPECT_EQ(model1.findItem(id2), parent2);
    EXPECT_EQ(model2.findItem(id2), parent2);
}
