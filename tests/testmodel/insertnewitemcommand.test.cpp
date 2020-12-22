// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/commands/insertnewitemcommand.h"

#include "google_test.h"
#include "mvvm/interfaces/itemfactoryinterface.h"
#include "mvvm/model/compounditem.h"
#include "mvvm/model/itempool.h"
#include "mvvm/model/itemutils.h"
#include "mvvm/model/sessionitem.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/model/taginfo.h"
#include <stdexcept>

using namespace ModelView;

class InsertNewItemCommandTest : public ::testing::Test {
public:
    std::unique_ptr<InsertNewItemCommand> create_command(SessionItem* parent, std::string tag,
                                                         int row)
    {
        auto factory_func = [parent]() {
            return parent->model()->factory()->createItem(Constants::BaseType);
        };
        return std::make_unique<InsertNewItemCommand>(factory_func, parent, TagRow{tag, row});
    }
};

//! Insert new item through InsertNewItemCommand command.

TEST_F(InsertNewItemCommandTest, insertNewItemCommand)
{
    SessionModel model;

    // command to insert item in a model
    auto command = create_command(model.rootItem(), "", 0);

    // executing command
    command->execute();
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);
    EXPECT_EQ(std::get<SessionItem*>(command->result()), model.rootItem()->getItem("", 0));
    EXPECT_EQ(command->isObsolete(), false);

    // undoing command
    command->undo();
    EXPECT_EQ(model.rootItem()->childrenCount(), 0);
    EXPECT_EQ(std::get<SessionItem*>(command->result()), nullptr);
    EXPECT_EQ(command->isObsolete(), false);

    // executing again
    command->execute();
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);
    EXPECT_EQ(std::get<SessionItem*>(command->result()), model.rootItem()->getItem("", 0));
    EXPECT_EQ(command->isObsolete(), false);
}

//! Insert new item through InsertNewItemCommand command.

TEST_F(InsertNewItemCommandTest, insertNewItemWithTagCommand)
{
    SessionModel model;

    // command to insert parent in the model
    auto command1 = create_command(model.rootItem(), "", 0);
    command1->execute(); // insertion
    EXPECT_EQ(command1->isObsolete(), false);

    auto parent = std::get<SessionItem*>(command1->result());
    parent->registerTag(TagInfo::universalTag("tag1"), /*set_as_default*/ true);
    EXPECT_EQ(parent->childrenCount(), 0);

    // command to insert child
    auto command2 = create_command(parent, "tag1", 0);
    command2->execute(); // insertion
    EXPECT_EQ(command2->isObsolete(), false);

    EXPECT_EQ(parent->childrenCount(), 1);
    EXPECT_EQ(Utils::ChildAt(parent, 0), std::get<SessionItem*>(command2->result()));

    // undoing command
    command2->undo();
    EXPECT_EQ(parent->childrenCount(), 0);
    EXPECT_EQ(nullptr, std::get<SessionItem*>(command2->result()));
    EXPECT_EQ(command2->isObsolete(), false);
}

//! Attempt to execute command twice.

TEST_F(InsertNewItemCommandTest, attemptToExecuteTwice)
{
    SessionModel model;
    // command to set same value
    auto command = create_command(model.rootItem(), "", 0);

    // executing command
    command->execute();
    EXPECT_THROW(command->execute(), std::runtime_error);
}

//! Attempt to undo command twice.

TEST_F(InsertNewItemCommandTest, attemptToUndoTwice)
{
    SessionModel model;

    // command to set same value
    auto command = create_command(model.rootItem(), "", 0);

    // executing command
    command->execute();
    command->undo();
    EXPECT_THROW(command->undo(), std::runtime_error);
}

//! Attempt to insert second property to the compount item.

TEST_F(InsertNewItemCommandTest, attemptInsertSecondProperty)
{
    SessionModel model;
    auto parent = model.insertItem<CompoundItem>();
    parent->registerTag(TagInfo::propertyTag("radius", Constants::PropertyType));

    // command to insert second property
    auto factory_func = [parent]() {
        return parent->model()->factory()->createItem(Constants::PropertyType);
    };

    // adding property to another tag is valid
    InsertNewItemCommand command1(factory_func, parent, TagRow{"radius", -1});
    EXPECT_NO_THROW(command1.execute());
    EXPECT_FALSE(command1.isObsolete());
    EXPECT_EQ(std::get<SessionItem*>(command1.result()), parent->getItem("radius"));

    // adding second property to the same tag is not possible. Command should be in obsolete state
    InsertNewItemCommand command2(factory_func, parent, TagRow{"radius", -1});
    EXPECT_NO_THROW(command2.execute());
    EXPECT_TRUE(command2.isObsolete());
    EXPECT_EQ(std::get<SessionItem*>(command2.result()), nullptr);

    // undoing failed command shouldn't be possible
    EXPECT_THROW(command2.undo(), std::runtime_error);
}

//! Insert new item through InsertNewItemCommand command.
//! We validate that undoing, and then redoing, would restore very first unique identifier.

TEST_F(InsertNewItemCommandTest, insertNewPropertyItemPreservedId)
{
    SessionModel model;
    // command to insert second property
    auto factory_func = [&model]() { return model.factory()->createItem(Constants::PropertyType); };

    EXPECT_EQ(model.rootItem()->childrenCount(), 0);

    InsertNewItemCommand command1(factory_func, model.rootItem(), TagRow{"", 0});
    command1.execute();

    EXPECT_EQ(model.rootItem()->childrenCount(), 1);
    auto orig_identifier = model.rootItem()->children()[0]->identifier();

    command1.undo();
    EXPECT_EQ(model.rootItem()->childrenCount(), 0);

    command1.execute();
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);
    EXPECT_EQ(model.rootItem()->children()[0]->identifier(), orig_identifier);
}

//! Insert new item through InsertNewItemCommand command.
//! We validate that undoing, and then redoing, would restore very first unique identifier.
//! Same as above, but we additionally controling item pool.

TEST_F(InsertNewItemCommandTest, insertNewPropertyItemIdInPool)
{
    auto pool = std::make_shared<ItemPool>();
    SessionModel model("Model", pool);
    // command to insert second property
    auto factory_func = [&model]() { return model.factory()->createItem(Constants::PropertyType); };

    EXPECT_EQ(model.rootItem()->childrenCount(), 0);
    EXPECT_EQ(pool->size(), 1); // rootItem

    InsertNewItemCommand command1(factory_func, model.rootItem(), TagRow{"", 0});
    command1.execute();

    EXPECT_EQ(model.rootItem()->childrenCount(), 1);
    auto orig_identifier = model.rootItem()->children()[0]->identifier();
    EXPECT_EQ(pool->size(), 2);

    command1.undo();
    EXPECT_EQ(model.rootItem()->childrenCount(), 0);

    command1.execute();
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);
    auto restored_item = model.rootItem()->children()[0];
    EXPECT_EQ(restored_item->identifier(), orig_identifier);
    EXPECT_EQ(model.findItem(orig_identifier), restored_item);
    EXPECT_EQ(pool->item_for_key(orig_identifier), restored_item);
}
