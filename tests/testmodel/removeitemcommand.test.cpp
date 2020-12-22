// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/commands/removeitemcommand.h"

#include "google_test.h"
#include "mvvm/model/compounditem.h"
#include "mvvm/model/itemutils.h"
#include "mvvm/model/sessionitem.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/model/taginfo.h"

using namespace ModelView;

class RemoveItemCommandTest : public ::testing::Test {
};

TEST_F(RemoveItemCommandTest, removeAtCommand)
{
    SessionModel model;
    auto item = model.insertItem<SessionItem>(model.rootItem());

    auto item_identifier = item->identifier();

    // command to insert parent in the model
    auto command = std::make_unique<RemoveItemCommand>(model.rootItem(), TagRow{"", 0});
    command->execute(); // removal

    EXPECT_EQ(std::get<bool>(command->result()), true);
    EXPECT_EQ(model.rootItem()->childrenCount(), 0);
    EXPECT_FALSE(command->isObsolete());

    // undo command
    command->undo();
    EXPECT_FALSE(command->isObsolete());
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);
    auto restored = Utils::ChildAt(model.rootItem(), 0);
    EXPECT_EQ(restored->identifier(), item_identifier);
}

TEST_F(RemoveItemCommandTest, removeAtCommandChild)
{
    SessionModel model;
    auto parent = model.insertItem<SessionItem>(model.rootItem());
    parent->registerTag(TagInfo::universalTag("tag1"), /*set_as_default*/ true);

    auto child1 = model.insertItem<SessionItem>(parent);
    child1->setData(42.0);
    model.insertItem<SessionItem>(parent);

    auto child1_identifier = child1->identifier();

    // command to remove one child
    auto command = std::make_unique<RemoveItemCommand>(parent, TagRow{"", 0});
    command->execute(); // removal

    // check that one child was removed
    EXPECT_FALSE(command->isObsolete());
    EXPECT_EQ(std::get<bool>(command->result()), true);
    EXPECT_EQ(parent->childrenCount(), 1);

    // undo command
    command->undo();
    EXPECT_FALSE(command->isObsolete());
    EXPECT_EQ(parent->childrenCount(), 2);
    auto restored = Utils::ChildAt(parent, 0);
    EXPECT_EQ(restored->identifier(), child1_identifier);

    // checking the data of restored item
    EXPECT_EQ(restored->data<double>(), 42.0);
}

TEST_F(RemoveItemCommandTest, removeAtCommandParentWithChild)
{
    SessionModel model;
    auto parent = model.insertItem<SessionItem>(model.rootItem());
    parent->registerTag(TagInfo::universalTag("tag1"), /*set_as_default*/ true);

    auto child1 = model.insertItem<SessionItem>(parent);
    child1->setData(42.0);

    auto parent_identifier = parent->identifier();
    auto child1_identifier = child1->identifier();

    // command to remove parent
    auto command = std::make_unique<RemoveItemCommand>(model.rootItem(), TagRow{"", 0});
    command->execute(); // removal
    EXPECT_FALSE(command->isObsolete());

    // check that one child was removed
    EXPECT_EQ(std::get<bool>(command->result()), true);
    EXPECT_EQ(model.rootItem()->childrenCount(), 0);

    // undo command
    command->undo();
    EXPECT_FALSE(command->isObsolete());
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);
    auto restored_parent = Utils::ChildAt(model.rootItem(), 0);
    auto restored_child = Utils::ChildAt(restored_parent, 0);

    EXPECT_EQ(restored_parent->identifier(), parent_identifier);
    EXPECT_EQ(restored_child->identifier(), child1_identifier);

    // checking the data of restored item
    EXPECT_EQ(restored_child->data<double>(), 42.0);
}

//! RemoveAtCommand in multitag context

TEST_F(RemoveItemCommandTest, removeAtCommandMultitag)
{
    SessionModel model;
    auto parent = model.insertItem<SessionItem>(model.rootItem());
    parent->registerTag(TagInfo::universalTag("tag1"));
    parent->registerTag(TagInfo::universalTag("tag2"));

    auto child1 = model.insertItem<SessionItem>(parent, "tag1");
    child1->setData(41.0);

    auto child2 = model.insertItem<SessionItem>(parent, "tag1");
    child2->setData(42.0);

    auto child3 = model.insertItem<SessionItem>(parent, "tag2");
    child3->setData(43.0);

    auto parent_identifier = parent->identifier();
    auto child1_identifier = child1->identifier();
    auto child2_identifier = child2->identifier();
    auto child3_identifier = child3->identifier();

    // command to remove parent
    auto command = std::make_unique<RemoveItemCommand>(parent, TagRow{"tag1", 1});
    command->execute(); // removal

    // check that one child was removed
    EXPECT_FALSE(command->isObsolete());
    EXPECT_EQ(std::get<bool>(command->result()), true);
    EXPECT_EQ(parent->childrenCount(), 2);

    // undo command
    command->undo();
    EXPECT_FALSE(command->isObsolete());
    EXPECT_EQ(parent->childrenCount(), 3);
    auto restored_parent = Utils::ChildAt(model.rootItem(), 0);
    auto restored_child2 = Utils::ChildAt(restored_parent, 1);

    EXPECT_EQ(restored_parent->identifier(), parent_identifier);
    EXPECT_EQ(restored_child2->identifier(), child2_identifier);

    // checking the data of restored item
    EXPECT_EQ(restored_child2->data<double>(), 42.0);
}

//! Attempt to remove property item.

TEST_F(RemoveItemCommandTest, attemptToRemoveItem)
{
    SessionModel model;
    auto parent = model.insertItem<CompoundItem>(model.rootItem());
    parent->addProperty("thickness", 42.0);

    auto command = std::make_unique<RemoveItemCommand>(parent, TagRow{"thickness", 0});
    command->execute();

    EXPECT_TRUE(command->isObsolete());
    EXPECT_EQ(std::get<bool>(command->result()), false);
}
