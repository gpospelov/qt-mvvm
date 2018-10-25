#include <gtest/gtest.h>
#include "path.h"
#include "sessionmodel.h"
#include "sessionitem.h"
#include <memory>

using namespace ModelView;

class TestPath : public ::testing::Test
{
public:
    ~TestPath();
};

TestPath::~TestPath() = default;

TEST_F(TestPath, initialState)
{
    Path path;
    EXPECT_TRUE(path.str().empty());
}

TEST_F(TestPath, append)
{
    Path path;
    path.append(1);
    EXPECT_EQ(path.str(), "1");

    path.append(2);
    EXPECT_EQ(path.str(), "1,2");

    path.prepend(3);
    EXPECT_EQ(path.str(), "3,1,2");
}

TEST_F(TestPath, fromVector)
{
    Path path = Path::fromVector({1,2,3});
    EXPECT_EQ(path.str(), "1,2,3");
}

TEST_F(TestPath, fromString)
{
    Path path = Path::fromString("3,2,3");
    EXPECT_EQ(path.str(), "3,2,3");
}

TEST_F(TestPath, pathFromItem)
{
    const model_type modelType("abc");
    SessionModel model;

    // unexisting path
    EXPECT_TRUE(model.pathFromItem(nullptr).str().empty());
    // yet another unexisting path
    std::unique_ptr<SessionItem> xx(new SessionItem);
    EXPECT_TRUE(model.pathFromItem(xx.get()).str().empty());

    // three children beneeth root item
    SessionItem* item0 = model.insertNewItem(modelType);
    SessionItem* item1 = model.insertNewItem(modelType);
    SessionItem* item2 = model.insertNewItem(modelType);

    EXPECT_EQ(model.pathFromItem(item0).str(), "0");
    EXPECT_EQ(model.pathFromItem(item1).str(), "1");
    EXPECT_EQ(model.pathFromItem(item2).str(), "2");

    // adding granchildren to item0
    SessionItem* child00 = model.insertNewItem(modelType, item0);
    SessionItem* child01 = model.insertNewItem(modelType, item0);

    EXPECT_EQ(model.pathFromItem(child00).str(), "0,0");
    EXPECT_EQ(model.pathFromItem(child01).str(), "0,1");

    // adding grandchildren to item2
    SessionItem* child20 = model.insertNewItem(modelType, item2);
    SessionItem* child200 = model.insertNewItem(modelType, child20);
    SessionItem* child201 = model.insertNewItem(modelType, child20);

    EXPECT_EQ(model.pathFromItem(child200).str(), "2,0,0");
    EXPECT_EQ(model.pathFromItem(child201).str(), "2,0,1");
}

TEST_F(TestPath, itemFromPath)
{
    const model_type modelType("abc");
    SessionModel model;

    // access to non-existing item
    Path non_existing;
    non_existing.append(8);
    EXPECT_EQ(model.itemFromPath(non_existing), nullptr);

    SessionItem* item0 = model.insertNewItem(modelType);
    SessionItem* item1 = model.insertNewItem(modelType);
    SessionItem* item2 = model.insertNewItem(modelType);

    EXPECT_EQ(model.itemFromPath(Path::fromVector({0})), item0);
    EXPECT_EQ(model.itemFromPath(Path::fromVector({1})), item1);
    EXPECT_EQ(model.itemFromPath(Path::fromVector({2})), item2);

    SessionItem* child20 = model.insertNewItem(modelType, item2);
    SessionItem* child200 = model.insertNewItem(modelType, child20);
    SessionItem* child201 = model.insertNewItem(modelType, child20);

    EXPECT_EQ(model.itemFromPath(Path::fromVector({2,0})), child20);
    EXPECT_EQ(model.itemFromPath(Path::fromVector({2,0,0})), child200);
    EXPECT_EQ(model.itemFromPath(Path::fromVector({2,0,1})), child201);
}
