#include "google_test.h"
#include "itemutils.h"
#include "removeitemcommand.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "taginfo.h"
#include "test_utils.h"
#include <QDebug>

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
    auto item = model.insertNewItem(Constants::BaseType, model.rootItem(), "", 0);

    auto item_identifier = item->data(ItemDataRole::IDENTIFIER).value<std::string>();

    // command to insert parent in the model
    auto command = std::make_unique<RemoveItemCommand>(model.rootItem(), "", 0);
    command->redo(); // removal

    EXPECT_EQ(command->result(), true);
    EXPECT_EQ(model.rootItem()->childrenCount(), 0);

    // undo command
    command->undo();
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);
    auto restored = Utils::ChildAt(model.rootItem(), 0);
    EXPECT_EQ(restored->data(ItemDataRole::IDENTIFIER).value<std::string>(), item_identifier);
}

TEST_F(TestRemoveItemCommand, removeAtCommandChild)
{
    SessionModel model;
    auto parent = model.insertNewItem(Constants::BaseType, model.rootItem(), "", 0);
    parent->registerTag(TagInfo::universalTag("tag1"), /*set_as_default*/ true);

    auto child1 = model.insertNewItem(Constants::BaseType, parent, "tag1", -1);
    child1->setData(42.0, ItemDataRole::DATA);
    model.insertNewItem(Constants::BaseType, parent, "tag1", -1);

    auto child1_identifier = child1->data(ItemDataRole::IDENTIFIER).value<std::string>();

    // command to remove one child
    auto command = std::make_unique<RemoveItemCommand>(parent, "", 0);
    command->redo(); // removal

    // check that one child was removed
    EXPECT_EQ(command->result(), true);
    EXPECT_EQ(parent->childrenCount(), 1);

    // undo command
    command->undo();
    EXPECT_EQ(parent->childrenCount(), 2);
    auto restored = Utils::ChildAt(parent, 0);
    EXPECT_EQ(restored->data(ItemDataRole::IDENTIFIER).value<std::string>(), child1_identifier);

    // checking the data of restored item
    EXPECT_EQ(restored->data(ItemDataRole::DATA).toDouble(), 42.0);
}

TEST_F(TestRemoveItemCommand, removeAtCommandParentWithChild)
{
    SessionModel model;
    auto parent = model.insertNewItem(Constants::BaseType, model.rootItem(), "", 0);
    parent->registerTag(TagInfo::universalTag("tag1"), /*set_as_default*/ true);

    auto child1 = model.insertNewItem(Constants::BaseType, parent, "tag1", -1);
    child1->setData(42.0, ItemDataRole::DATA);

    auto parent_identifier = parent->data(ItemDataRole::IDENTIFIER).value<std::string>();
    auto child1_identifier = child1->data(ItemDataRole::IDENTIFIER).value<std::string>();

    // command to remove parent
    auto command = std::make_unique<RemoveItemCommand>(model.rootItem(), "", 0);
    command->redo(); // removal

    // check that one child was removed
    EXPECT_EQ(command->result(), true);
    EXPECT_EQ(model.rootItem()->childrenCount(), 0);

    // undo command
    command->undo();
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);
    auto restored_parent = Utils::ChildAt(model.rootItem(), 0);
    auto restored_child = Utils::ChildAt(restored_parent, 0);

    EXPECT_EQ(restored_parent->data(ItemDataRole::IDENTIFIER).value<std::string>(),
              parent_identifier);
    EXPECT_EQ(restored_child->data(ItemDataRole::IDENTIFIER).value<std::string>(),
              child1_identifier);

    // checking the data of restored item
    EXPECT_EQ(restored_child->data(ItemDataRole::DATA).toDouble(), 42.0);
}

//! RemoveAtCommand in multitag context

TEST_F(TestRemoveItemCommand, removeAtCommandMultitag)
{
    SessionModel model;
    auto parent = model.insertNewItem(Constants::BaseType, model.rootItem(), "", 0);
    parent->registerTag(TagInfo::universalTag("tag1"));
    parent->registerTag(TagInfo::universalTag("tag2"));

    auto child1 = model.insertNewItem(Constants::BaseType, parent, "tag1", -1);
    child1->setData(41.0, ItemDataRole::DATA);

    auto child2 = model.insertNewItem(Constants::BaseType, parent, "tag1", -1);
    child2->setData(42.0, ItemDataRole::DATA);

    auto child3 = model.insertNewItem(Constants::BaseType, parent, "tag2", -1);
    child3->setData(43.0, ItemDataRole::DATA);

    auto parent_identifier = parent->data(ItemDataRole::IDENTIFIER).value<std::string>();
    auto child1_identifier = child1->data(ItemDataRole::IDENTIFIER).value<std::string>();
    auto child2_identifier = child2->data(ItemDataRole::IDENTIFIER).value<std::string>();
    auto child3_identifier = child3->data(ItemDataRole::IDENTIFIER).value<std::string>();

    // command to remove parent
    auto command = std::make_unique<RemoveItemCommand>(parent, "tag1", 1);
    command->redo(); // removal

    // check that one child was removed
    EXPECT_EQ(command->result(), true);
    EXPECT_EQ(parent->childrenCount(), 2);

    // undo command
    command->undo();
    EXPECT_EQ(parent->childrenCount(), 3);
    auto restored_parent = Utils::ChildAt(model.rootItem(), 0);
    auto restored_child2 = Utils::ChildAt(restored_parent, 1);

    EXPECT_EQ(restored_parent->data(ItemDataRole::IDENTIFIER).value<std::string>(),
              parent_identifier);
    EXPECT_EQ(restored_child2->data(ItemDataRole::IDENTIFIER).value<std::string>(),
              child2_identifier);

    // checking the data of restored item
    EXPECT_EQ(restored_child2->data(ItemDataRole::DATA).toDouble(), 42.0);
}
