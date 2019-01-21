#include "google_test.h"
#include "sessionmodel.h"
#include "sessionitem.h"
#include "taginfo.h"
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

    const model_type modelType("abc");

    // inserting single item
    auto item = model.insertNewItem(modelType);
    EXPECT_TRUE(item != nullptr);
    EXPECT_EQ(item->parent(), model.rootItem());
    EXPECT_EQ(item->model(), &model);
    EXPECT_EQ(item->modelType(), modelType);

    // adding child to it
    auto child = model.insertNewItem(modelType, item);
    EXPECT_TRUE(child != nullptr);
    EXPECT_EQ(child->parent(), item);
    EXPECT_EQ(child->model(), &model);
    EXPECT_EQ(child->modelType(), modelType);

    // taking child back
    auto taken = item->takeItem(0);
    EXPECT_EQ(taken, child);
    EXPECT_EQ(child->model(), nullptr);
    delete taken;
}

TEST_F(TestSessionModel, insertNewItemWithTag)
{
    const std::string tag1("tag1");
    SessionModel model;
    auto parent = model.insertNewItem("parentModel");
    parent->registerTag(TagInfo::universalTag(tag1));
    auto child1 = model.insertNewItem("childModel", parent, -1, tag1);

    EXPECT_EQ(parent->tagFromItem(child1), tag1);
    EXPECT_EQ(parent->rowOfChild(child1), 0);

    // adding second child
    auto child2 = model.insertNewItem("childModel", parent, 0, tag1);

    EXPECT_EQ(parent->tagFromItem(child2), tag1);
    EXPECT_EQ(parent->rowOfChild(child1), 1);
    EXPECT_EQ(parent->rowOfChild(child2), 0);
}


TEST_F(TestSessionModel, setData)
{
    SessionModel model;
    const int role = ItemDataRole::DISPLAY;

    // inserting single item
    auto item = model.insertNewItem("abc");
    EXPECT_FALSE(model.data(item, role).isValid());

    // setting new data
    QVariant value(42.0);
    model.setData(item, value, role);
    EXPECT_EQ(model.data(item, role), value);
}

TEST_F(TestSessionModel, removeRow)
{
    SessionModel model;

    auto parent = model.insertNewItem("MultiLayer");
    auto child1 = model.insertNewItem("Layer1", parent);
    auto child2 = model.insertNewItem("Layer2", parent, 0); // before child1
    Q_UNUSED(child2);

    // removing child2
    model.removeRow(parent, 0); // removing child2
    EXPECT_EQ(parent->childrenCount(), 1);
    EXPECT_EQ(parent->childAt(0), child1);
}
