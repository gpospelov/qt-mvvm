#include "insertnewitemcommand.h"
#include "google_test.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "taginfo.h"
#include "itemutils.h"

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

TEST_F(TestInsertNewItemCommand, insertNewItemWithTagCommand)
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
