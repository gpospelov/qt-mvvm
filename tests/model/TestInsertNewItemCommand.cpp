#include "google_test.h"
#include "insertnewitemcommand.h"
#include "itemfactoryinterface.h"
#include "itemutils.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "taginfo.h"

using namespace ModelView;

class TestInsertNewItemCommand : public ::testing::Test
{
public:
    ~TestInsertNewItemCommand();
    std::unique_ptr<InsertNewItemCommand> create_command(SessionItem* parent, std::string tag,
                                                         int row)
    {
        auto factory_func = [parent]() {
            return parent->model()->factory()->createItem(Constants::BaseType);
        };
        return std::make_unique<InsertNewItemCommand>(factory_func, parent, tag, row);
    }
};

TestInsertNewItemCommand::~TestInsertNewItemCommand() = default;

//! Insert new item through InsertNewItemCommand command.

TEST_F(TestInsertNewItemCommand, insertNewItemCommand)
{
    SessionModel model;

    // command to insert item in a model
    auto command = create_command(model.rootItem(), "", 0);

    // executing command
    command->execute();
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);
    EXPECT_EQ(command->result(), model.rootItem()->getItem("", 0));

    // undoing command
    command->undo();
    EXPECT_EQ(model.rootItem()->childrenCount(), 0);
    EXPECT_EQ(command->result(), nullptr);
}

//! Insert new item through InsertNewItemCommand command.

TEST_F(TestInsertNewItemCommand, insertNewItemWithTagCommand)
{
    SessionModel model;

    // command to insert parent in the model
    auto command1 = create_command(model.rootItem(), "", 0);
    command1->execute(); // insertion

    auto parent = command1->result();
    parent->registerTag(TagInfo::universalTag("tag1"), /*set_as_default*/ true);
    EXPECT_EQ(parent->childrenCount(), 0);

    // command to insert child
    auto command2 = create_command(parent, "tag1", 0);
    command2->execute(); // insertion

    EXPECT_EQ(parent->childrenCount(), 1);
    EXPECT_EQ(Utils::ChildAt(parent, 0), command2->result());

    // undoing command
    command2->undo();
    EXPECT_EQ(parent->childrenCount(), 0);
    EXPECT_EQ(nullptr, command2->result());
}

//! Attempt to execute command twice.

TEST_F(TestInsertNewItemCommand, attemptToExecuteTwice)
{
    SessionModel model;
    // command to set same value
    auto command = create_command(model.rootItem(), "", 0);

    // executing command
    command->execute();
    EXPECT_THROW(command->execute(), std::runtime_error);
}

//! Attempt to undo command twice.

TEST_F(TestInsertNewItemCommand, attemptToUndoTwice)
{
    SessionModel model;

    // command to set same value
    auto command = create_command(model.rootItem(), "", 0);

    // executing command
    command->execute();
    command->undo();
    EXPECT_THROW(command->undo(), std::runtime_error);
}
