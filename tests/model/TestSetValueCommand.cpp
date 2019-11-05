#include <mvvm/commands/setvaluecommand.h>
#include "google_test.h"
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>

using namespace ModelView;

class TestSetValueCommand : public ::testing::Test
{
public:
    ~TestSetValueCommand();
};

TestSetValueCommand::~TestSetValueCommand() = default;

//! Set item value through SetValueCommand command.

TEST_F(TestSetValueCommand, setValueCommand)
{
    SessionModel model;
    const int role = ItemDataRole::DATA;

    // inserting single item
    auto item = model.insertItem<SessionItem>();
    EXPECT_FALSE(model.data(item, role).isValid());

    QVariant expected(42.0);
    auto command = std::make_unique<SetValueCommand>(item, expected, role);

    // executing command
    command->execute();
    EXPECT_TRUE(command->result()); // value was changed
    EXPECT_EQ(model.data(item, role), expected);

    // undoing command
    command->undo();
    EXPECT_TRUE(command->result()); // value was changed
    EXPECT_FALSE(model.data(item, role).isValid());
}

//! Set same item value through SetValueCommand command.

TEST_F(TestSetValueCommand, setSameValueCommand)
{
    SessionModel model;
    const int role = ItemDataRole::DATA;

    // inserting single item
    auto item = model.insertItem<SessionItem>();
    QVariant expected(42.0);
    item->setData(expected, role);

    // command to set same value
    auto command = std::make_unique<SetValueCommand>(item, expected, role);

    // executing command
    command->execute();
    EXPECT_FALSE(command->result()); // value wasn't changed
    EXPECT_EQ(model.data(item, role), expected);

    // undoing command
    command->undo();
    EXPECT_FALSE(command->result()); // value wasn't changed
    EXPECT_EQ(model.data(item, role), expected);
}

