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

TEST_F(TestMoveItemCommand, rootContextNext)
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
    EXPECT_EQ(command.isObsolete(), false);

    expected = {item0, item2, item1, item3};
    EXPECT_EQ(model.rootItem()->children(), expected);
}

TEST_F(TestMoveItemCommand, rootContextSamePos)
{
    SessionModel model;
    auto item0 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);
    auto item1 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);
    auto item2 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);
    auto item3 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);

    // expecting 4 items in the order of insertion
    std::vector<SessionItem*> expected = {item0, item1, item2, item3};
    EXPECT_EQ(model.rootItem()->children(), expected);

    // moving item1 to the same position
    MoveItemCommand command(item1, model.rootItem(), "", 1);
    command.execute();
    EXPECT_EQ(command.result(), true);

    // expecting new order of items
    expected = {item0, item1, item2, item3};
    EXPECT_EQ(model.rootItem()->children(), expected);

    // undoing command
    command.undo();
    EXPECT_EQ(command.result(), true);
    EXPECT_EQ(command.isObsolete(), false);

    expected = {item0, item1, item2, item3};
    EXPECT_EQ(model.rootItem()->children(), expected);
}

TEST_F(TestMoveItemCommand, rootContextBack)
{
    SessionModel model;
    auto item0 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);
    auto item1 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);
    auto item2 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);
    auto item3 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);

    // expecting 4 items in the order of insertion
    std::vector<SessionItem*> expected = {item0, item1, item2, item3};
    EXPECT_EQ(model.rootItem()->children(), expected);

    // moving item2 to item1's place
    MoveItemCommand command(item2, model.rootItem(), "", 1);
    command.execute();
    EXPECT_EQ(command.result(), true);

    // expecting new order of items
    expected = {item0, item2, item1, item3};
    EXPECT_EQ(model.rootItem()->children(), expected);

    // undoing command
    command.undo();
    EXPECT_EQ(command.result(), true);
    EXPECT_EQ(command.isObsolete(), false);

    expected = {item0, item1, item2, item3};
    EXPECT_EQ(model.rootItem()->children(), expected);
}

TEST_F(TestMoveItemCommand, rootContextLast)
{
    SessionModel model;
    auto item0 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);
    auto item1 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);
    auto item2 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);
    auto item3 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);

    // expecting 4 items in the order of insertion
    std::vector<SessionItem*> expected = {item0, item1, item2, item3};
    EXPECT_EQ(model.rootItem()->children(), expected);

    // moving item0 in the back of the list
    MoveItemCommand command(item0, model.rootItem(), "", -1);
    command.execute();
    EXPECT_EQ(command.result(), true);
    EXPECT_EQ(command.isObsolete(), false);

    // expecting new order of items
    expected = {item1, item2, item3, item0};
    EXPECT_EQ(model.rootItem()->children(), expected);

    // undoing command
    command.undo();
    EXPECT_EQ(command.result(), true);
    EXPECT_EQ(command.isObsolete(), false);

    expected = {item0, item1, item2, item3};
    EXPECT_EQ(model.rootItem()->children(), expected);
}

TEST_F(TestMoveItemCommand, fromRootToParent)
{
    SessionModel model;
    auto item0 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);
    auto parent = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);
    parent->registerTag(TagInfo::universalTag("tag1"), /*set_as_default*/ true);

    auto child0 = model.insertNewItem(Constants::BaseType, parent, "tag1", -1);
    auto child1 = model.insertNewItem(Constants::BaseType, parent, "tag1", -1);

    // expected items for root item
    std::vector<SessionItem*> expected = {item0, parent};
    EXPECT_EQ(model.rootItem()->children(), expected);

    // expected items for parent
    expected = {child0, child1};
    EXPECT_EQ(parent->children(), expected);

    // moving item0 from root to parent
    MoveItemCommand command(item0, parent, "", 1);
    command.execute();
    EXPECT_EQ(command.result(), true);
    EXPECT_EQ(command.isObsolete(), false);

    // expected items for root item
    expected = {parent};
    EXPECT_EQ(model.rootItem()->children(), expected);

    // expected items for parent
    expected = {child0, item0, child1};
    EXPECT_EQ(parent->children(), expected);

    // undoing command
    command.undo();
    EXPECT_EQ(command.result(), true);
    EXPECT_EQ(command.isObsolete(), false);

    // expected items for root item
    expected = {item0, parent};
    EXPECT_EQ(model.rootItem()->children(), expected);

    // expected items for parent
    expected = {child0, child1};
    EXPECT_EQ(parent->children(), expected);
}

TEST_F(TestMoveItemCommand, fromParentToRoot)
{
    SessionModel model;
    auto item0 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);
    auto parent = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);
    parent->registerTag(TagInfo::universalTag("tag1"), /*set_as_default*/ true);

    auto child0 = model.insertNewItem(Constants::BaseType, parent, "tag1", -1);
    auto child1 = model.insertNewItem(Constants::BaseType, parent, "tag1", -1);

    // expected items for root item
    std::vector<SessionItem*> expected = {item0, parent};
    EXPECT_EQ(model.rootItem()->children(), expected);

    // expected items for parent
    expected = {child0, child1};
    EXPECT_EQ(parent->children(), expected);

    // moving child0 from parent to root
    MoveItemCommand command(child0, model.rootItem(), "", 0);
    command.execute();
    EXPECT_EQ(command.result(), true);
    EXPECT_EQ(command.isObsolete(), false);

    // expected items for root item
    expected = {child0, item0, parent};
    EXPECT_EQ(model.rootItem()->children(), expected);

    // expected items for parent
    expected = {child1};
    EXPECT_EQ(parent->children(), expected);

    // undoing command
    command.undo();
    EXPECT_EQ(command.result(), true);
    EXPECT_EQ(command.isObsolete(), false);

    // expected items for root item
    expected = {item0, parent};
    EXPECT_EQ(model.rootItem()->children(), expected);

    // expected items for parent
    expected = {child0, child1};
    EXPECT_EQ(parent->children(), expected);
}

TEST_F(TestMoveItemCommand, betweenParentTags)
{
    SessionModel model;
    auto parent = model.insertNewItem(Constants::BaseType, model.rootItem(), "", -1);
    parent->registerTag(TagInfo::universalTag("tag1"));
    parent->registerTag(TagInfo::universalTag("tag2"));

    auto child0 = model.insertNewItem(Constants::BaseType, parent, "tag1", -1);
    auto child1 = model.insertNewItem(Constants::BaseType, parent, "tag1", -1);
    auto child2 = model.insertNewItem(Constants::BaseType, parent, "tag2", -1);
    auto child3 = model.insertNewItem(Constants::BaseType, parent, "tag2", -1);

    // expected items for root item
    std::vector<SessionItem*> expected = {parent};
    EXPECT_EQ(model.rootItem()->children(), expected);

    // expected items for parent
    expected = {child0, child1, child2, child3};
    EXPECT_EQ(parent->children(), expected);

    // moving child2 to another tag
    MoveItemCommand command(child2, parent, "tag1", 0);
    command.execute();
    EXPECT_EQ(command.result(), true);
    EXPECT_EQ(command.isObsolete(), false);

    // expected items for root item
    expected = {parent};
    EXPECT_EQ(model.rootItem()->children(), expected);

    // expected items for parents tag
    expected = {child2, child0, child1, child3};
    EXPECT_EQ(parent->children(), expected);
    expected = {child2, child0, child1};
    EXPECT_EQ(parent->getItems("tag1"), expected);
    expected = {child3};
    EXPECT_EQ(parent->getItems("tag2"), expected);

    // undoing command
    command.undo();
    EXPECT_EQ(command.result(), true);
    EXPECT_EQ(command.isObsolete(), false);

    // expected items for root item
    expected = {parent};
    EXPECT_EQ(model.rootItem()->children(), expected);

    // expected items for parent
    expected = {child0, child1};
    EXPECT_EQ(parent->getItems("tag1"), expected);
    expected = {child2, child3};
    EXPECT_EQ(parent->getItems("tag2"), expected);
}





