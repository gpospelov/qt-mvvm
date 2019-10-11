#include "insertnewitemcommand.h"
#include "google_test.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "taginfo.h"
#include "itemutils.h"
#include "itemfactoryinterface.h"

using namespace ModelView;

class TestInsertNewItemCommand : public ::testing::Test
{
public:
    ~TestInsertNewItemCommand();
};

TestInsertNewItemCommand::~TestInsertNewItemCommand() = default;

//! Insert new item through InsertNewItemCommand command.

TEST_F(TestInsertNewItemCommand, insertNewItemCommand)
{
    SessionModel model;

    auto create_func = [&model](){return model.factory()->createItem(Constants::BaseType);};

    // command to set same value
    auto command =
        std::make_unique<InsertNewItemCommand>(Constants::BaseType, create_func, model.rootItem(), "", 0);

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
    auto create_func = [&model](){return model.factory()->createItem(Constants::BaseType);};

    // command to insert parent in the model
    auto command1 =
        std::make_unique<InsertNewItemCommand>(Constants::BaseType, create_func, model.rootItem(), "", 0);
    command1->execute(); // insertion

    auto parent = command1->result();
    parent->registerTag(TagInfo::universalTag("tag1"), /*set_as_default*/ true);
    EXPECT_EQ(parent->childrenCount(), 0);

    // command to insert child
    auto command2 = std::make_unique<InsertNewItemCommand>(Constants::BaseType, create_func, parent, "tag1", 0);
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
    auto create_func = [&model](){return model.factory()->createItem(Constants::BaseType);};

    // command to set same value
    auto command =
        std::make_unique<InsertNewItemCommand>(Constants::BaseType, create_func, model.rootItem(), "", 0);

    // executing command
    command->execute();
    EXPECT_THROW(command->execute(), std::runtime_error);
}

//! Attempt to undo command twice.

TEST_F(TestInsertNewItemCommand, attemptToUndoTwice)
{
    SessionModel model;
    auto create_func = [&model](){return model.factory()->createItem(Constants::BaseType);};

    // command to set same value
    auto command =
        std::make_unique<InsertNewItemCommand>(Constants::BaseType, create_func, model.rootItem(), "", 0);

    // executing command
    command->execute();
    command->undo();
    EXPECT_THROW(command->undo(), std::runtime_error);
}
