#include "google_test.h"
#include "commands.h"
#include "sessionitem.h"
#include "sessionmodel.h"

using namespace ModelView;

class TestCommands : public ::testing::Test
{
public:
    ~TestCommands();
};

TestCommands::~TestCommands() = default;

//! Set item value through the command.

TEST_F(TestCommands, setValueCommand)
{
    SessionModel model;
    const int role = ItemDataRole::DISPLAY;

    // inserting single item
    auto item = model.insertNewItem("abc");
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

//! Set same item value through the command.

TEST_F(TestCommands, setSameValueCommand)
{
    SessionModel model;
    const int role = ItemDataRole::DISPLAY;

    // inserting single item
    auto item = model.insertNewItem("abc");
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
