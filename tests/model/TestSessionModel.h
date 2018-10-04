#include <gtest/gtest.h>
#include "sessionmodel.h"
#include "sessionitem.h"
#include <memory>

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
    SessionModel model;

    // inserting single item
    auto item = model.insertNewItem();
    EXPECT_EQ(item->parent(), model.rootItem());
    EXPECT_EQ(item->model(), &model);

    // adding child to it
    auto child = model.insertNewItem(item);
    EXPECT_EQ(child->parent(), item);
    EXPECT_EQ(child->model(), &model);

    // taking child back
    auto taken = item->takeRow(0);
    EXPECT_EQ(taken, child);
    EXPECT_EQ(child->model(), nullptr);
    delete taken;
}

TEST_F(TestSessionModel, setData)
{
    SessionModel model;
    const int role = Qt::DisplayRole;

    // inserting single item
    auto item = model.insertNewItem();
    EXPECT_FALSE(model.data(item, role).isValid());

    // setting new data
    QVariant value(42.0);
    model.setData(item, value, role);
    EXPECT_EQ(model.data(item, role), value);
}
