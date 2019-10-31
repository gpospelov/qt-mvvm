#include "google_test.h"
#include "itemutils.h"
#include "removeitemcommand.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "taginfo.h"

using namespace ModelView;

class TestRemoveItemCommand : public ::testing::Test
{
public:
    ~TestRemoveItemCommand();
};

TestRemoveItemCommand::~TestRemoveItemCommand() = default;

TEST_F(TestRemoveItemCommand, removeAtCommand)
{
    SessionModel model;
    auto item = model.insertItem<SessionItem>(model.rootItem(), "", 0);

    auto item_identifier = item->identifier();

    // command to insert parent in the model
    auto command = std::make_unique<RemoveItemCommand>(model.rootItem(), TagRow{"", 0});
    command->execute(); // removal

    EXPECT_EQ(command->result(), true);
    EXPECT_EQ(model.rootItem()->childrenCount(), 0);

    // undo command
    command->undo();
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);
    auto restored = Utils::ChildAt(model.rootItem(), 0);
    EXPECT_EQ(restored->identifier(), item_identifier);
}

TEST_F(TestRemoveItemCommand, removeAtCommandChild)
{
    SessionModel model;
    auto parent = model.insertItem<SessionItem>(model.rootItem(), "", 0);
    parent->registerTag(TagInfo::universalTag("tag1"), /*set_as_default*/ true);

    auto child1 = model.insertItem<SessionItem>(parent, "tag1", -1);
    child1->setData(42.0);
    model.insertItem<SessionItem>(parent, "tag1", -1);

    auto child1_identifier = child1->identifier();

    // command to remove one child
    auto command = std::make_unique<RemoveItemCommand>(parent, TagRow{"", 0});
    command->execute(); // removal

    // check that one child was removed
    EXPECT_EQ(command->result(), true);
    EXPECT_EQ(parent->childrenCount(), 1);

    // undo command
    command->undo();
    EXPECT_EQ(parent->childrenCount(), 2);
    auto restored = Utils::ChildAt(parent, 0);
    EXPECT_EQ(restored->identifier(), child1_identifier);

    // checking the data of restored item
    EXPECT_EQ(restored->data().value<double>(), 42.0);
}

TEST_F(TestRemoveItemCommand, removeAtCommandParentWithChild)
{
    SessionModel model;
    auto parent = model.insertItem<SessionItem>(model.rootItem(), "", 0);
    parent->registerTag(TagInfo::universalTag("tag1"), /*set_as_default*/ true);

    auto child1 = model.insertItem<SessionItem>(parent, "tag1", -1);
    child1->setData(42.0);

    auto parent_identifier = parent->identifier();
    auto child1_identifier = child1->identifier();

    // command to remove parent
    auto command = std::make_unique<RemoveItemCommand>(model.rootItem(), TagRow{"", 0});
    command->execute(); // removal

    // check that one child was removed
    EXPECT_EQ(command->result(), true);
    EXPECT_EQ(model.rootItem()->childrenCount(), 0);

    // undo command
    command->undo();
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);
    auto restored_parent = Utils::ChildAt(model.rootItem(), 0);
    auto restored_child = Utils::ChildAt(restored_parent, 0);

    EXPECT_EQ(restored_parent->identifier(), parent_identifier);
    EXPECT_EQ(restored_child->identifier(), child1_identifier);

    // checking the data of restored item
    EXPECT_EQ(restored_child->data().value<double>(), 42.0);
}

//! RemoveAtCommand in multitag context

TEST_F(TestRemoveItemCommand, removeAtCommandMultitag)
{
    SessionModel model;
    auto parent = model.insertItem<SessionItem>(model.rootItem(), "", 0);
    parent->registerTag(TagInfo::universalTag("tag1"));
    parent->registerTag(TagInfo::universalTag("tag2"));

    auto child1 = model.insertItem<SessionItem>(parent, "tag1", -1);
    child1->setData(41.0);

    auto child2 = model.insertItem<SessionItem>(parent, "tag1", -1);
    child2->setData(42.0);

    auto child3 = model.insertItem<SessionItem>(parent, "tag2", -1);
    child3->setData(43.0);

    auto parent_identifier = parent->identifier();
    auto child1_identifier = child1->identifier();
    auto child2_identifier = child2->identifier();
    auto child3_identifier = child3->identifier();

    // command to remove parent
    auto command = std::make_unique<RemoveItemCommand>(parent, TagRow{"tag1", 1});
    command->execute(); // removal

    // check that one child was removed
    EXPECT_EQ(command->result(), true);
    EXPECT_EQ(parent->childrenCount(), 2);

    // undo command
    command->undo();
    EXPECT_EQ(parent->childrenCount(), 3);
    auto restored_parent = Utils::ChildAt(model.rootItem(), 0);
    auto restored_child2 = Utils::ChildAt(restored_parent, 1);

    EXPECT_EQ(restored_parent->identifier(), parent_identifier);
    EXPECT_EQ(restored_child2->identifier(), child2_identifier);

    // checking the data of restored item
    EXPECT_EQ(restored_child2->data().value<double>(), 42.0);
}
