#include "google_test.h"
#include "itemmanager.h"
#include "itempool.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "taginfo.h"
#include "itemutils.h"
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

TEST_F(TestSessionModel, insertNewItem)
{
    SessionModel model;

    const model_type modelType = Constants::BaseType;

    // inserting single item
    auto item = model.insertNewItem(modelType);
    EXPECT_TRUE(item != nullptr);
    EXPECT_EQ(item->parent(), model.rootItem());
    EXPECT_EQ(item->model(), &model);
    EXPECT_EQ(item->modelType(), modelType);

    // checking registration
    auto item_key = item->data(ItemDataRole::IDENTIFIER).value<std::string>();
    EXPECT_EQ(model.manager()->itemPool()->item_for_key(item_key), item);

    // registering tag
    item->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);

    // adding child to it
    auto child = model.insertNewItem(modelType, item);
    auto child_key = child->data(ItemDataRole::IDENTIFIER).value<std::string>();
    EXPECT_EQ(model.manager()->itemPool()->item_for_key(child_key), child);

    EXPECT_TRUE(child != nullptr);
    EXPECT_EQ(child->parent(), item);
    EXPECT_EQ(child->model(), &model);
    EXPECT_EQ(child->modelType(), modelType);

    // taking child back
    auto taken = item->takeItem("", 0);
    EXPECT_EQ(taken, child);
    EXPECT_EQ(child->model(), nullptr);

    // childitem not registered anymore
    EXPECT_EQ(model.manager()->itemPool()->item_for_key(child_key), nullptr);

    delete taken;
}

TEST_F(TestSessionModel, insertNewItemWithTag)
{
    const std::string tag1("tag1");
    SessionModel model;
    auto parent = model.insertNewItem(Constants::BaseType);
    parent->registerTag(TagInfo::universalTag(tag1));
    auto child1 = model.insertNewItem(Constants::PropertyType, parent, tag1, -1);

    EXPECT_EQ(parent->tagFromItem(child1), tag1);
    EXPECT_EQ(Utils::IndexOfChild(parent, child1), 0);

    // adding second child
    auto child2 = model.insertNewItem(Constants::PropertyType, parent, tag1, 0);

    EXPECT_EQ(parent->tagFromItem(child2), tag1);
    EXPECT_EQ(Utils::IndexOfChild(parent, child1), 1);
    EXPECT_EQ(Utils::IndexOfChild(parent, child2), 0);
}

TEST_F(TestSessionModel, setData)
{
    SessionModel model;

    // inserting single item
    auto item = model.insertNewItem(Constants::BaseType);
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

TEST_F(TestSessionModel, removeRow)
{
    SessionModel model;

    auto parent = model.insertNewItem(Constants::BaseType);
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);

    auto child1 = model.insertNewItem(Constants::BaseType, parent);
    auto child2 = model.insertNewItem(Constants::PropertyType, parent, "", 0); // before child1
    Q_UNUSED(child2)

    // removing child2
    model.removeItem(parent, "", 0); // removing child2
    EXPECT_EQ(parent->childrenCount(), 1);
    EXPECT_EQ(Utils::ChildAt(parent, 0), child1);

    // child2 shouldn't be registered anymore
    EXPECT_EQ(model.manager()->itemPool()->key_for_item(child2), "");
}

TEST_F(TestSessionModel, takeRowFromRootItem)
{
    SessionModel model;

    auto parent = model.insertNewItem(Constants::BaseType);
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);
    auto parent_key = parent->data(ItemDataRole::IDENTIFIER).value<std::string>();

    auto child = model.insertNewItem(Constants::PropertyType, parent);
    auto child_key = child->data(ItemDataRole::IDENTIFIER).value<std::string>();

    EXPECT_EQ(model.manager()->itemPool()->item_for_key(parent_key), parent);
    EXPECT_EQ(model.manager()->itemPool()->item_for_key(child_key), child);

    // taking parent
    auto taken = model.rootItem()->takeItem("", 0);
    EXPECT_EQ(model.manager()->itemPool()->item_for_key(parent_key), nullptr);
    EXPECT_EQ(model.manager()->itemPool()->item_for_key(child_key), nullptr);
    delete taken;
}

TEST_F(TestSessionModel, clearModel)
{
    auto pool = std::make_shared<ItemPool>();
    SessionModel model("test", pool);

    EXPECT_EQ(pool->size(), 1);

    auto first_root = model.rootItem();

    EXPECT_EQ(model.rootItem()->childrenCount(), 0);
    model.insertNewItem(Constants::BaseType);
    model.insertNewItem(Constants::BaseType);
    EXPECT_EQ(model.rootItem()->childrenCount(), 2);

    model.clear();
    EXPECT_EQ(model.rootItem()->childrenCount(), 0);
    EXPECT_FALSE(model.rootItem() == first_root);
    EXPECT_EQ(pool->key_for_item(first_root), "");
    EXPECT_EQ(pool->size(), 1);
}
