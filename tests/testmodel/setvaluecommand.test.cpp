// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <mvvm/commands/setvaluecommand.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <stdexcept>

using namespace ModelView;

class SetValueCommandTest : public ::testing::Test
{
public:
    ~SetValueCommandTest();
};

SetValueCommandTest::~SetValueCommandTest() = default;

//! Set item value through SetValueCommand command.

TEST_F(SetValueCommandTest, setValueCommand)
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
    EXPECT_TRUE(std::get<bool>(command->result())); // value was changed
    EXPECT_EQ(command->isObsolete(), false);
    EXPECT_EQ(model.data(item, role), expected);

    // undoing command
    command->undo();
    EXPECT_TRUE(std::get<bool>(command->result())); // value was changed
    EXPECT_FALSE(model.data(item, role).isValid());
    EXPECT_EQ(command->isObsolete(), false);
}

//! Set same item value through SetValueCommand command.

TEST_F(SetValueCommandTest, setSameValueCommand)
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
    EXPECT_FALSE(std::get<bool>(command->result())); // value wasn't changed
    EXPECT_EQ(model.data(item, role), expected);
    EXPECT_EQ(command->isObsolete(), true);

    // undoing command which is in isObsolete state is not possible
    EXPECT_THROW(command->undo(), std::runtime_error);
}
