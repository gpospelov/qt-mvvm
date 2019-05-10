#include "commands.h"
#include "removeitemcommand.h"
#include "google_test.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "taginfo.h"
#include "test_utils.h"
#include "itemutils.h"
#include <QDebug>

using namespace ModelView;

class TestCommands : public ::testing::Test
{
public:
    ~TestCommands();
};

TestCommands::~TestCommands() = default;

//! Set item value through SetValueCommand command.

TEST_F(TestCommands, setValueCommand)
{
    SessionModel model;
    const int role = ItemDataRole::DATA;

    // inserting single item
    auto item = model.insertNewItem(Constants::BaseType);
    EXPECT_FALSE(model.data(item, role).isValid());

    QVariant expected(42.0);
    auto command = std::make_unique<SetValueCommand>(item, expected, role);

    // executing command
    command->redo();
    EXPECT_TRUE(command->result()); // value was changed
    EXPECT_EQ(model.data(item, role), expected);

    // undoing command
    command->undo();
    EXPECT_TRUE(command->result()); // value was changed
    EXPECT_FALSE(model.data(item, role).isValid());
}

//! Set same item value through SetValueCommand command.

TEST_F(TestCommands, setSameValueCommand)
{
    SessionModel model;
    const int role = ItemDataRole::DATA;

    // inserting single item
    auto item = model.insertNewItem(Constants::BaseType);
    QVariant expected(42.0);
    item->setData(expected, role);

    // command to set same value
    auto command = std::make_unique<SetValueCommand>(item, expected, role);

    // executing command
    command->redo();
    EXPECT_FALSE(command->result()); // value wasn't changed
    EXPECT_EQ(model.data(item, role), expected);

    // undoing command
    command->undo();
    EXPECT_FALSE(command->result()); // value wasn't changed
    EXPECT_EQ(model.data(item, role), expected);
}

//! Insert new item through InsertNewItemCommand command.

TEST_F(TestCommands, insertNewItemCommand)
{
    SessionModel model;

    // command to set same value
    auto command =
        std::make_unique<InsertNewItemCommand>(Constants::BaseType, model.rootItem(), "", 0);

    // executing command
    command->redo();
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);
    EXPECT_EQ(command->result(), model.rootItem()->getItem("", 0));

    // undoing command
    command->undo();
    EXPECT_EQ(model.rootItem()->childrenCount(), 0);
    EXPECT_EQ(command->result(), nullptr);
}

//! Insert new item through InsertNewItemCommand command.

TEST_F(TestCommands, insertNewItemWithTagCommand)
{
    SessionModel model;

    // command to insert parent in the model
    auto command1 =
        std::make_unique<InsertNewItemCommand>(Constants::BaseType, model.rootItem(), "", 0);
    command1->redo(); // insertion

    auto parent = command1->result();
    parent->registerTag(TagInfo::universalTag("tag1"), /*set_as_default*/ true);
    EXPECT_EQ(parent->childrenCount(), 0);

    // command to insert child
    auto command2 = std::make_unique<InsertNewItemCommand>(Constants::BaseType, parent, "tag1", 0);
    command2->redo(); // insertion

    EXPECT_EQ(parent->childrenCount(), 1);
    EXPECT_EQ(Utils::ChildAt(parent, 0), command2->result());

    // undoing command
    command2->undo();
    EXPECT_EQ(parent->childrenCount(), 0);
    EXPECT_EQ(nullptr, command2->result());
}
