#include "google_test.h"
#include "itemutils.h"
#include "moveitemcommand.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "taginfo.h"

using namespace ModelView;

class TestMoveItemCommand : public ::testing::Test
{
public:
    ~TestMoveItemCommand();
};

TestMoveItemCommand::~TestMoveItemCommand() = default;

TEST_F(TestMoveItemCommand, moveAtRootContext)
{
    SessionModel model;
    auto item0 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);
    auto item1 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);
    auto item2 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);
    auto item3 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);

    // expecting 4 items in the order of insertion
    std::vector<SessionItem*> expected = {item0, item1, item2, item3};
    EXPECT_EQ(model.rootItem()->children(), expected);

    // moving item1 to the next position
    MoveItemCommand command(item1, model.rootItem(), "", 2);
    command.execute();
    EXPECT_EQ(command.result(), true);

    // expecting new order of items
    expected = {item0, item2, item1, item3};
    EXPECT_EQ(model.rootItem()->children(), expected);

    // undoing command
    command.undo();
    EXPECT_EQ(command.result(), true);
    expected = {item0, item1, item2, item3};
    EXPECT_EQ(model.rootItem()->children(), expected);

    // redoing
    command.execute();
    EXPECT_EQ(command.result(), true);
    expected = {item0, item2, item1, item3};
    EXPECT_EQ(model.rootItem()->children(), expected);
}

TEST_F(TestMoveItemCommand, moveAtRootContextSamePos)
{
    SessionModel model;
    auto item0 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);
    auto item1 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);
    auto item2 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);
    auto item3 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);

    // expecting 4 items in the order of insertion
    std::vector<SessionItem*> expected = {item0, item1, item2, item3};
    EXPECT_EQ(model.rootItem()->children(), expected);

    // moving item1 to the next position
    MoveItemCommand command(item1, model.rootItem(), "", 1);
    command.execute();
    EXPECT_EQ(command.result(), true);

    // expecting new order of items
    expected = {item0, item1, item2, item3};
    EXPECT_EQ(model.rootItem()->children(), expected);

    // undoing command
    command.undo();
    EXPECT_EQ(command.result(), true);
    expected = {item0, item1, item2, item3};
    EXPECT_EQ(model.rootItem()->children(), expected);
}

TEST_F(TestMoveItemCommand, moveAtRootContextForward)
{
    SessionModel model;
    auto item0 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);
    auto item1 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);
    auto item2 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);
    auto item3 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);

    // expecting 4 items in the order of insertion
    std::vector<SessionItem*> expected = {item0, item1, item2, item3};
    EXPECT_EQ(model.rootItem()->children(), expected);

    // moving item1 to the next position
    MoveItemCommand command(item2, model.rootItem(), "", 1);
    command.execute();
    EXPECT_EQ(command.result(), true);

    // expecting new order of items
    expected = {item0, item2, item1, item3};
    EXPECT_EQ(model.rootItem()->children(), expected);

    // undoing command
    command.undo();
    EXPECT_EQ(command.result(), true);
    expected = {item0, item1, item2, item3};
    EXPECT_EQ(model.rootItem()->children(), expected);
}

TEST_F(TestMoveItemCommand, moveAtRootContextMoveBack)
{
    SessionModel model;
    auto item0 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);
    auto item1 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);
    auto item2 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);
    auto item3 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);

    // expecting 4 items in the order of insertion
    std::vector<SessionItem*> expected = {item0, item1, item2, item3};
    EXPECT_EQ(model.rootItem()->children(), expected);

    // moving item1 to the next position
    MoveItemCommand command(item0, model.rootItem(), "", -1);
    command.execute();
    EXPECT_EQ(command.result(), true);

    // expecting new order of items
    expected = {item1, item2, item3, item0};
    EXPECT_EQ(model.rootItem()->children(), expected);

    // undoing command
    command.undo();
    expected = {item0, item1, item2, item3};
    EXPECT_EQ(model.rootItem()->children(), expected);
}
