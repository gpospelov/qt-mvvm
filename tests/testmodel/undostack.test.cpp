// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "toyitems.h"
#include "toymodel.h"
#include "toyitems.h"
#include <mvvm/commands/commandadapter.h>
#include <mvvm/commands/setvaluecommand.h>
#include <mvvm/commands/undostack.h>
#include <mvvm/interfaces/undostackinterface.h>
#include <mvvm/model/itemutils.h>
#include <mvvm/model/propertyitem.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/model/taginfo.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/graphitem.h>

using namespace ModelView;

class UndoStackTest : public ::testing::Test
{
public:
    ~UndoStackTest();
};

UndoStackTest::~UndoStackTest() = default;

//! Checking time of life of the command during undo/redo.
//! This is connected with the fact, that Qt takes ownership of the command and we have to use
//! our own wrapper.

TEST_F(UndoStackTest, commandTimeOfLife)
{
    SessionModel model;
    auto item = model.insertItem<PropertyItem>();
    item->setData(42);

    std::weak_ptr<SetValueCommand> pw_command; // to trace command time of life

    UndoStack stack;

    {
        // creating command
        auto command =
            std::make_shared<SetValueCommand>(item, QVariant::fromValue(43), ItemDataRole::DATA);
        pw_command = command;
        EXPECT_EQ(pw_command.use_count(), 1);

        // checking state of item, stack and command
        EXPECT_EQ(item->data<int>(), 42);
        EXPECT_FALSE(stack.canRedo());
        EXPECT_FALSE(stack.canUndo());
        EXPECT_EQ(stack.index(), 0);
        EXPECT_EQ(stack.count(), 0);
        EXPECT_EQ(command->isObsolete(), false);
        EXPECT_FALSE(std::get<bool>(command->result()));

        // adding command to the stack, it will lead to command execution
        stack.execute(command);
        EXPECT_EQ(pw_command.use_count(), 2);

        // checking state of item, stack and command
        EXPECT_EQ(item->data<int>(), 43);
        EXPECT_FALSE(stack.canRedo());
        EXPECT_TRUE(stack.canUndo());
        EXPECT_EQ(stack.index(), 1);
        EXPECT_EQ(stack.count(), 1);
        EXPECT_EQ(command->isObsolete(), false);
        EXPECT_TRUE(std::get<bool>(command->result()));

        // undoing
        stack.undo();
        EXPECT_EQ(item->data<int>(), 42);
        EXPECT_TRUE(stack.canRedo());
        EXPECT_FALSE(stack.canUndo());
        EXPECT_EQ(stack.index(), 0);
        EXPECT_EQ(stack.count(), 1);
        EXPECT_EQ(command->isObsolete(), false);
        EXPECT_TRUE(std::get<bool>(command->result()));

        // redoing
        stack.redo();
        EXPECT_EQ(item->data<int>(), 43);
        EXPECT_FALSE(stack.canRedo());
        EXPECT_TRUE(stack.canUndo());
        EXPECT_EQ(stack.index(), 1);
        EXPECT_EQ(stack.count(), 1);
        EXPECT_EQ(command->isObsolete(), false);
        EXPECT_TRUE(std::get<bool>(command->result()));
    }

    EXPECT_EQ(pw_command.use_count(), 1);
    if (auto command = pw_command.lock()) {
        EXPECT_EQ(command->isObsolete(), false);
        EXPECT_TRUE(std::get<bool>(command->result()));
    }
}

//! Checking time of life of the command during undo/redo.
//! Same as above, but command is trying to set same value. It makes it "expired" and it should
//! be removed from the stack.

TEST_F(UndoStackTest, expiredCommandTimeOfLife)
{
    SessionModel model;
    auto item = model.insertItem<PropertyItem>();
    item->setData(42);

    std::weak_ptr<SetValueCommand> pw_command; // to trace command time of life

    UndoStack stack;

    {
        // creating command which sets the same value
        auto command =
            std::make_shared<SetValueCommand>(item, QVariant::fromValue(42), ItemDataRole::DATA);
        pw_command = command;
        EXPECT_EQ(pw_command.use_count(), 1);

        // checking state of item, stack and command
        EXPECT_EQ(item->data<int>(), 42);
        EXPECT_FALSE(stack.canRedo());
        EXPECT_FALSE(stack.canUndo());
        EXPECT_EQ(stack.index(), 0);
        EXPECT_EQ(stack.count(), 0);
        EXPECT_EQ(command->isObsolete(), false);
        EXPECT_FALSE(std::get<bool>(command->result()));

        // adding command to the stack, it will lead to command execution
        stack.execute(command);
        EXPECT_EQ(pw_command.use_count(), 1); // was already deleted from the stack

        // checking state of item, stack and command
        EXPECT_EQ(item->data<int>(), 42);
        EXPECT_FALSE(stack.canRedo());
        EXPECT_FALSE(stack.canUndo());
        EXPECT_EQ(stack.index(), 0);
        EXPECT_EQ(stack.count(), 0);
        EXPECT_EQ(command->isObsolete(), true);
        EXPECT_FALSE(std::get<bool>(command->result()));
    }

    EXPECT_EQ(pw_command.use_count(), 0);
    EXPECT_EQ(pw_command.lock(), nullptr);
}

TEST_F(UndoStackTest, initialState)
{
    SessionModel model;

    // no undo/redo stack by default
    EXPECT_TRUE(model.undoStack() == nullptr);

    // switching undo/redo on
    model.setUndoRedoEnabled(true);
    auto stack = model.undoStack();
    EXPECT_TRUE(stack != nullptr);

    // initial state of undo redo stack
    EXPECT_TRUE(stack->isActive());
    EXPECT_FALSE(stack->canRedo());
    EXPECT_FALSE(stack->canUndo());
    EXPECT_EQ(stack->index(), 0);
}

TEST_F(UndoStackTest, insertNewItem)
{
    const model_type modelType(Constants::BaseType);
    SessionModel model;
    model.setUndoRedoEnabled(true);
    auto stack = model.undoStack();

    // inserting single item
    auto item = model.insertItem<SessionItem>();
    EXPECT_TRUE(item != nullptr);
    EXPECT_EQ(item->modelType(), Constants::BaseType);
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);
    EXPECT_EQ(stack->index(), 1);
    EXPECT_EQ(stack->count(), 1);
    EXPECT_FALSE(stack->canRedo());
    EXPECT_TRUE(stack->canUndo());

    // undoing item insertion
    stack->undo();
    EXPECT_EQ(model.rootItem()->childrenCount(), 0);
    EXPECT_EQ(stack->index(), 0);
    EXPECT_EQ(stack->count(), 1);
    EXPECT_TRUE(stack->canRedo());
    EXPECT_FALSE(stack->canUndo());

    // redoing item insertion
    stack->redo();
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);
    EXPECT_EQ(Utils::ChildAt(model.rootItem(), 0)->modelType(), modelType);
    EXPECT_EQ(stack->index(), 1);
    EXPECT_FALSE(stack->canRedo());
    EXPECT_TRUE(stack->canUndo());

    // clearing stack
    stack->clear();
    EXPECT_EQ(stack->index(), 0);
    EXPECT_FALSE(stack->canRedo());
    EXPECT_FALSE(stack->canUndo());
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);
    EXPECT_EQ(Utils::ChildAt(model.rootItem(), 0)->modelType(), modelType);
}

//! Insert property item, unto, redo, and checking that identifier is preserved.

TEST_F(UndoStackTest, insertPropertyItemID)
{
    SessionModel model;
    model.setUndoRedoEnabled(true);
    auto stack = model.undoStack();

    auto item = model.insertItem<PropertyItem>();
    auto original_id = item->identifier();

    EXPECT_EQ(stack->index(), 1);
    EXPECT_EQ(stack->count(), 1);

    model.undoStack()->undo();
    EXPECT_EQ(model.rootItem()->childrenCount(), 0);

    model.undoStack()->redo();
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);

    auto restored_property_item = Utils::ChildAt(model.rootItem(), 0);
    EXPECT_EQ(restored_property_item->modelType(), Constants::PropertyType);
    EXPECT_EQ(restored_property_item->identifier(), original_id);
}

//! Undo/redo scenario when few items inserted.

TEST_F(UndoStackTest, insertParentAndChild)
{
    SessionModel model;
    model.setUndoRedoEnabled(true);
    auto stack = model.undoStack();

    auto parent = model.insertItem<SessionItem>();
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);

    model.insertItem<PropertyItem>(parent);
    model.insertItem<PropertyItem>(parent);

    // state of the stack after insertion of 3 items
    EXPECT_EQ(stack->count(), 3);
    EXPECT_EQ(stack->index(), 3);
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);
    EXPECT_EQ(parent->childrenCount(), 2);

    // undoing two last insertions
    stack->undo();
    stack->undo();
    EXPECT_EQ(stack->count(), 3);
    EXPECT_EQ(stack->index(), 1);
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);
    EXPECT_EQ(parent->childrenCount(), 0);

    // redoing once
    stack->redo();
    EXPECT_EQ(stack->count(), 3);
    EXPECT_EQ(stack->index(), 2);
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);
    EXPECT_EQ(parent->childrenCount(), 1);
    EXPECT_EQ(Utils::ChildAt(parent, 0)->modelType(), Constants::PropertyType);
}

//! Undo/redo scenario when item inserted and data set few times.

TEST_F(UndoStackTest, setData)
{
    const int role = ItemDataRole::DATA;
    SessionModel model;
    model.setUndoRedoEnabled(true);
    auto stack = model.undoStack();

    // creating item
    auto item = model.insertItem<SessionItem>();
    EXPECT_FALSE(model.data(item, role).isValid());

    // setting new data
    QVariant value(42.0);
    model.setData(item, value, role);
    EXPECT_EQ(model.data(item, role), value);

    EXPECT_EQ(stack->index(), 2); // insert and setData commands
    EXPECT_FALSE(model.undoStack()->canRedo());
    EXPECT_TRUE(model.undoStack()->canUndo());

    // undoing and checking
    stack->undo();
    EXPECT_EQ(stack->index(), 1);
    EXPECT_FALSE(model.data(item, role).isValid());

    // setting data three times
    model.setData(item, QVariant::fromValue(42.0), role);
    model.setData(item, QVariant::fromValue(43.0), role);
    model.setData(item, QVariant::fromValue(44.0), role);
    EXPECT_EQ(stack->index(), 4);
    EXPECT_EQ(model.data(item, role).value<double>(), 44.0);
    stack->undo();
    stack->undo();
    EXPECT_EQ(model.data(item, role).value<double>(), 42.0);
    stack->redo();
    stack->redo();
    EXPECT_EQ(model.data(item, role).value<double>(), 44.0);
}

//! Undo/redo scenario when item data changed through item and not the model.

TEST_F(UndoStackTest, setDataThroughItem)
{
    const int role = ItemDataRole::DATA;
    const QVariant value(42.0);

    SessionModel model;
    model.setUndoRedoEnabled(true);
    auto stack = model.undoStack();

    // creating item
    auto item = model.insertItem<SessionItem>();
    EXPECT_FALSE(model.data(item, role).isValid());

    // setting new data through item (and not through model)
    item->setData(value, role);
    EXPECT_EQ(item->data<QVariant>(role), value);

    EXPECT_EQ(stack->index(), 2); // insert and setData commands
    EXPECT_FALSE(model.undoStack()->canRedo());
    EXPECT_TRUE(model.undoStack()->canUndo());

    // undoing and checking
    stack->undo();
    EXPECT_EQ(stack->index(), 1);
    EXPECT_FALSE(model.data(item, role).isValid());
}

//! Undo/redo scenario when we set same data. Undo stack should be empty.

TEST_F(UndoStackTest, setSameData)
{
    SessionModel model;
    auto item = model.insertItem<PropertyItem>();
    item->setData(42.0);

    model.setUndoRedoEnabled(true);
    auto stack = model.undoStack();
    EXPECT_EQ(stack->index(), 0);
    EXPECT_FALSE(model.undoStack()->canRedo());
    EXPECT_FALSE(model.undoStack()->canUndo());

    // setting same data should not lead to appearance of command in a stack
    item->setData(42.0);
    EXPECT_EQ(stack->index(), 0);
    EXPECT_FALSE(model.undoStack()->canRedo());
    EXPECT_FALSE(model.undoStack()->canUndo());
}

//! Checks if we insert item, set data and undo everything we can get back to the data.

TEST_F(UndoStackTest, insertAndSetData)
{
    const int role = ItemDataRole::DATA;
    SessionModel model;
    model.setUndoRedoEnabled(true);
    auto stack = model.undoStack();

    // creating item
    auto item = model.insertItem<SessionItem>();
    EXPECT_FALSE(model.data(item, role).isValid());

    // setting new data
    QVariant value(42.0);
    model.setData(item, value, role);
    EXPECT_EQ(model.data(item, role), value);

    EXPECT_EQ(stack->index(), 2); // insert and setData commands
    EXPECT_FALSE(model.undoStack()->canRedo());
    EXPECT_TRUE(model.undoStack()->canUndo());

    // undoing twice and checking
    stack->undo();
    stack->undo();
    EXPECT_EQ(stack->index(), 0);
    EXPECT_EQ(model.rootItem()->childrenCount(), 0);

    // returning all back
    stack->redo();
    stack->redo();
    EXPECT_EQ(stack->index(), 2);
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);
    item = Utils::ChildAt(model.rootItem(), 0);
    EXPECT_EQ(model.data(item, role).value<double>(), 42.0);
}

//! Inserting item, setting the data, removing row, undoing, checking item and data.

TEST_F(UndoStackTest, removeRow)
{
    const int role = ItemDataRole::DATA;
    const QVariant data(42);

    SessionModel model;
    model.setUndoRedoEnabled(true);
    auto stack = model.undoStack();

    auto item = model.insertItem<SessionItem>();
    item->setData(data, role);

    // initial state before removing the row
    EXPECT_EQ(stack->count(), 2); // insert and setData commands
    EXPECT_EQ(stack->index(), 2); // insert and setData commands
    EXPECT_FALSE(model.undoStack()->canRedo());
    EXPECT_TRUE(model.undoStack()->canUndo());
    EXPECT_EQ(item->data<QVariant>(role), data);
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);

    // removing the row
    model.removeItem(model.rootItem(), {"", 0});
    EXPECT_EQ(stack->count(), 3);
    EXPECT_EQ(stack->index(), 3);
    EXPECT_EQ(model.rootItem()->childrenCount(), 0);

    // undoing and checking the data
    stack->undo();
    EXPECT_EQ(stack->count(), 3);
    EXPECT_EQ(stack->index(), 2);
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);
    item = Utils::ChildAt(model.rootItem(), 0);
    EXPECT_EQ(model.data(item, role).value<double>(), 42.0);
    EXPECT_EQ(item->modelType(), Constants::BaseType);
}

//! Inserting parent and child, setting data to them, removing parent, undoing and checking.

TEST_F(UndoStackTest, removeParentAndChild)
{
    const int role1(ItemDataRole::DATA), role2(ItemDataRole::DISPLAY);
    const QVariant data1(42);
    const QVariant data2 = QVariant::fromValue(std::string("abc"));

    SessionModel model;
    model.setUndoRedoEnabled(true);
    auto stack = model.undoStack();

    auto parent = model.insertItem<SessionItem>();
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);

    parent->setData(data1, role1);
    auto child = model.insertItem<PropertyItem>(parent);
    child->setData(data2, role2);

    EXPECT_EQ(stack->count(), 4);
    EXPECT_EQ(stack->index(), 4);

    // removing parent
    model.removeItem(model.rootItem(), {"", 0});
    EXPECT_EQ(stack->count(), 5);
    EXPECT_EQ(stack->index(), 5);
    EXPECT_EQ(model.rootItem()->childrenCount(), 0);

    // undoing
    stack->undo();
    EXPECT_EQ(stack->count(), 5);
    EXPECT_EQ(stack->index(), 4);
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);
    auto parent_at = Utils::ChildAt(model.rootItem(), 0);
    auto child_at = Utils::ChildAt(parent_at, 0);

    EXPECT_EQ(parent_at->modelType(), Constants::BaseType);
    EXPECT_EQ(child_at->modelType(), Constants::PropertyType);

    EXPECT_EQ(parent_at->data<QVariant>(role1), data1);
    EXPECT_EQ(child_at->data<QVariant>(role2), data2);
}

//! Insert item, remove row, undo and check item id.

TEST_F(UndoStackTest, itemIdentifierOnRemove)
{
    SessionModel model;
    model.setUndoRedoEnabled(true);
    auto stack = model.undoStack();

    auto parent = model.insertItem<SessionItem>();
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);

    identifier_type parent_id = parent->identifier();
    auto child = model.insertItem<PropertyItem>(parent);
    identifier_type child_id = child->identifier();

    // removing parent
    model.removeItem(model.rootItem(), {"", 0});
    EXPECT_EQ(stack->count(), 3);
    EXPECT_EQ(stack->index(), 3);
    EXPECT_EQ(model.rootItem()->childrenCount(), 0);

    stack->undo();
    auto parent_at = Utils::ChildAt(model.rootItem(), 0);
    auto child_at = Utils::ChildAt(parent_at, 0);
    identifier_type parent_id2 = parent_at->identifier();
    identifier_type child_id2 = child_at->identifier();

    EXPECT_EQ(parent_id, parent_id2);
    EXPECT_EQ(child_id, child_id2);
}

//! Create multilayer, add two layers, remove everything and undo.
//! Toy models are used here.

TEST_F(UndoStackTest, multiLayer)
{
    auto pool = std::make_shared<ItemPool>();

    ToyItems::SampleModel model(pool);
    model.setUndoRedoEnabled(true);
    auto stack = model.undoStack();

    // creating multi layer
    auto parent = model.insertItem<ToyItems::MultiLayerItem>();
    EXPECT_TRUE(dynamic_cast<ToyItems::MultiLayerItem*>(parent) != nullptr);
    EXPECT_EQ(parent->modelType(), ToyItems::Constants::MultiLayerItemType);

    // inserting two layers
    auto layer0 = model.insertItem<ToyItems::LayerItem>(parent);
    auto layer1 = model.insertItem<ToyItems::LayerItem>(parent);

    // saving identifiers for further reference
    identifier_type id_parent = parent->identifier();
    identifier_type id_layer0 = layer0->identifier();
    identifier_type id_layer1 = layer1->identifier();

    // checking status of unddo stack
    EXPECT_EQ(stack->count(), 3);
    EXPECT_EQ(stack->index(), 3);

    // removing multi layer completely
    model.removeItem(model.rootItem(), {"", 0});
    EXPECT_EQ(stack->count(), 4);
    EXPECT_EQ(stack->index(), 4);
    EXPECT_EQ(model.rootItem()->childrenCount(), 0);

    // multilayer and its two layers should gone from registration
    EXPECT_TRUE(pool->item_for_key(id_parent) == nullptr);
    EXPECT_TRUE(pool->item_for_key(id_layer0) == nullptr);
    EXPECT_TRUE(pool->item_for_key(id_layer1) == nullptr);

    // undoing multilayer removal
    stack->undo();
    EXPECT_EQ(stack->count(), 4);
    EXPECT_EQ(stack->index(), 3);

    // restoring pointers back
    auto parent_at = Utils::ChildAt(model.rootItem(), 0);
    auto layer0_at = Utils::ChildAt(parent_at, 0);
    auto layer1_at = Utils::ChildAt(parent_at, 1);

    // checking that restored item has corrrect identifiers
    EXPECT_EQ(parent_at->identifier(), id_parent);
    EXPECT_EQ(layer0_at->identifier(), id_layer0);
    EXPECT_EQ(layer1_at->identifier(), id_layer1);

    // checking tag
    EXPECT_EQ(layer0_at->tag(), ToyItems::MultiLayerItem::T_LAYERS);
    EXPECT_EQ(layer1_at->tag(), ToyItems::MultiLayerItem::T_LAYERS);
    std::vector<SessionItem*> expected = {layer0_at, layer1_at};
    EXPECT_EQ(parent_at->getItems(ToyItems::MultiLayerItem::T_LAYERS), expected);
}

//! Move single layer from multilayer to another empty multilayer.

TEST_F(UndoStackTest, moveLayerFromMultiLayer)
{
    auto pool = std::make_shared<ItemPool>();

    ToyItems::SampleModel model(pool);
    model.setUndoRedoEnabled(true);
    auto stack = model.undoStack();

    // creating multi layer with 3 layers
    auto multilayer0 = model.insertItem<ToyItems::MultiLayerItem>();
    auto layer0 = model.insertItem<ToyItems::LayerItem>(multilayer0);
    auto multilayer1 = model.insertItem<ToyItems::MultiLayerItem>();

    // saving identifiers for further reference
    identifier_type id_multilayer0 = multilayer0->identifier();
    identifier_type id_layer0 = layer0->identifier();
    identifier_type id_multilayer1 = multilayer1->identifier();

    // moving layer from multilayer
    model.moveItem(layer0, multilayer1, {"", 0});

    // checking results
    std::vector<SessionItem*> expected = {layer0};
    EXPECT_EQ(multilayer0->children().size(), 0);
    EXPECT_EQ(multilayer1->children(), expected);
    EXPECT_EQ(pool->item_for_key(id_layer0), layer0);

    // undoing
    stack->undo();
    EXPECT_EQ(multilayer0->children(), expected);
    EXPECT_EQ(multilayer1->children().size(), 0);
    EXPECT_EQ(pool->item_for_key(id_layer0), layer0);
}

//! Move single layer from multilayer to another empty multilayer.
//! Delete second multilayer and undo.

TEST_F(UndoStackTest, moveLayerFromMLDeleteSecond)
{
    auto pool = std::make_shared<ItemPool>();

    ToyItems::SampleModel model(pool);
    model.setUndoRedoEnabled(true);
    auto stack = model.undoStack();

    // creating multi layer with 3 layers
    auto multilayer0 = model.insertItem<ToyItems::MultiLayerItem>();
    auto layer0 = model.insertItem<ToyItems::LayerItem>(multilayer0);
    auto multilayer1 = model.insertItem<ToyItems::MultiLayerItem>();

    // saving identifiers for further reference
    identifier_type id_multilayer0 = multilayer0->identifier();
    identifier_type id_layer0 = layer0->identifier();
    identifier_type id_multilayer1 = multilayer1->identifier();

    // moving layer from multilayer
    model.moveItem(layer0, multilayer1, {"", 0});

    // checking results
    std::vector<SessionItem*> expected = {layer0};
    EXPECT_EQ(multilayer0->children().size(), 0);
    EXPECT_EQ(multilayer1->children(), expected);
    EXPECT_EQ(pool->item_for_key(id_layer0), layer0);

    // deleting second multilayer
    model.removeItem(model.rootItem(), {"", 1});

    // undoing deletion
    stack->undo();

    // restoring ponters
    auto layer0_at = pool->item_for_key(id_layer0);
    auto multilayer1_at = pool->item_for_key(id_multilayer1);

    expected = {layer0_at};
    EXPECT_EQ(multilayer0->children().size(), 0);
    EXPECT_EQ(multilayer1_at->children(), expected);

    // unoing move
    stack->undo();

    EXPECT_EQ(multilayer0->children(), expected);
    EXPECT_EQ(multilayer1_at->children().size(), 0);
}

//! Create 2 multilayers, 3 layers each. Move layer from one multilayer to another.
//! Deleting everything and undoing.

TEST_F(UndoStackTest, moveLayerFromMLDeleteAll)
{
    auto pool = std::make_shared<ItemPool>();

    ToyItems::SampleModel model(pool);
    model.setUndoRedoEnabled(true);
    auto stack = model.undoStack();

    // creating multi layer with 3 layers
    auto multilayer0 = model.insertItem<ToyItems::MultiLayerItem>();
    auto layer0 = model.insertItem<ToyItems::LayerItem>(multilayer0);
    auto layer1 = model.insertItem<ToyItems::LayerItem>(multilayer0);
    auto layer2 = model.insertItem<ToyItems::LayerItem>(multilayer0);

    // saving identifiers for further reference
    identifier_type id_multilayer0 = multilayer0->identifier();
    identifier_type id_layer0 = layer0->identifier();
    identifier_type id_layer1 = layer1->identifier();
    identifier_type id_layer2 = layer2->identifier();

    // creating another multi layer with 3 layers
    auto multilayer1 = model.insertItem<ToyItems::MultiLayerItem>();
    auto layer3 = model.insertItem<ToyItems::LayerItem>(multilayer1);
    auto layer4 = model.insertItem<ToyItems::LayerItem>(multilayer1);
    auto layer5 = model.insertItem<ToyItems::LayerItem>(multilayer1);

    // saving identifiers for further reference
    identifier_type id_multilayer1 = multilayer1->identifier();
    identifier_type id_layer3 = layer3->identifier();
    identifier_type id_layer4 = layer4->identifier();
    identifier_type id_layer5 = layer5->identifier();

    // checking status of unddo stack
    EXPECT_EQ(stack->count(), 8);
    EXPECT_EQ(stack->index(), 8);

    // moving  layer1 to second multilayer
    model.moveItem(layer1, multilayer1, {ToyItems::MultiLayerItem::T_LAYERS, 0});

    // removing multilayers
    model.removeItem(model.rootItem(), {"", 1});
    model.removeItem(model.rootItem(), {"", 0});

    // checking status of unddo stack
    EXPECT_EQ(stack->count(), 11);
    EXPECT_EQ(stack->index(), 11);

    // undoing thrice
    stack->undo();
    stack->undo();
    stack->undo();

    // restoring pointers
    auto multilayer0_r = pool->item_for_key(id_multilayer0);
    auto layer0_r = pool->item_for_key(id_layer0);
    auto layer1_r = pool->item_for_key(id_layer1);
    auto layer2_r = pool->item_for_key(id_layer2);
    auto multilayer1_r = pool->item_for_key(id_multilayer1);
    auto layer3_r = pool->item_for_key(id_layer3);
    auto layer4_r = pool->item_for_key(id_layer4);
    auto layer5_r = pool->item_for_key(id_layer5);

    // checking layers
    std::vector<SessionItem*> expected = {layer0_r, layer1_r, layer2_r};
    EXPECT_EQ(multilayer0_r->children(), expected);

    expected = {layer3_r, layer4_r, layer5_r};
    EXPECT_EQ(multilayer1_r->children(), expected);
}

//! Creating two multilayers. Copying layer from one multilayer to another.

TEST_F(UndoStackTest, copyLayerFromMultilayer)
{
    auto pool = std::make_shared<ItemPool>();
    ToyItems::SampleModel model(pool);
    model.setUndoRedoEnabled(true);
    auto stack = model.undoStack();

    const double expected_thickness = 55.0;

    // creating multi layer with 3 layers
    auto multilayer0 = model.insertItem<ToyItems::MultiLayerItem>();
    auto layer0 = model.insertItem<ToyItems::LayerItem>(multilayer0);
    layer0->setProperty(ToyItems::LayerItem::P_THICKNESS, expected_thickness);
    auto multilayer1 = model.insertItem<ToyItems::MultiLayerItem>();

    // copying layer
    auto layer_copy = dynamic_cast<ToyItems::LayerItem*>(model.copyItem(layer0, multilayer1));
    EXPECT_EQ(multilayer1->itemCount(ToyItems::MultiLayerItem::T_LAYERS), 1);
    EXPECT_EQ(layer_copy->property<double>(ToyItems::LayerItem::P_THICKNESS), expected_thickness);
    EXPECT_TRUE(layer0->identifier() != layer_copy->identifier());

    auto id = layer_copy->identifier();
    EXPECT_EQ(pool->item_for_key(layer_copy->identifier()), layer_copy);

    // undoing
    stack->undo();
    EXPECT_EQ(multilayer1->itemCount(ToyItems::MultiLayerItem::T_LAYERS), 0);

    // redoing
    stack->redo();
    EXPECT_EQ(multilayer1->itemCount(ToyItems::MultiLayerItem::T_LAYERS), 1);
    EXPECT_EQ(multilayer1->getItems(ToyItems::MultiLayerItem::T_LAYERS)[0]->identifier(), id);
}

//! Add item and changing its data from macros.

TEST_F(UndoStackTest, beginMacrosEndMacros)
{
    const int role = ItemDataRole::DATA;
    const QVariant data(42);

    SessionModel model;
    model.setUndoRedoEnabled(true);
    auto stack = model.undoStack();

    stack->beginMacro("macro1");
    auto item = model.insertItem<SessionItem>();
    item->setData(data, role);
    stack->endMacro();

    // initial state before removing the row
    EXPECT_EQ(stack->count(), 1); // insert and setData commands
    EXPECT_EQ(stack->index(), 1); // insert and setData commands
    EXPECT_FALSE(model.undoStack()->canRedo());
    EXPECT_TRUE(model.undoStack()->canUndo());
    EXPECT_EQ(item->data<QVariant>(role), data);
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);

    // undoing and checking the data
    stack->undo();
    EXPECT_EQ(stack->count(), 1);
    EXPECT_EQ(stack->index(), 0);
    EXPECT_EQ(model.rootItem()->childrenCount(), 0);

    // redoing
    stack->redo();
    EXPECT_EQ(stack->count(), 1);
    EXPECT_EQ(stack->index(), 1);
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);
    item = Utils::ChildAt(model.rootItem(), 0);
    EXPECT_EQ(model.data(item, role).value<double>(), 42.0);
}

//! Add GraphItem and Data1DItem, addisgn data to graph, undo, then redo.
//! GraphItem should be pointing again to Data1DItem.
//! This is real bug case.

TEST_F(UndoStackTest, insertDataAndGraph)
{
    // constructing model with pool, enabling undo/redo
    auto pool = std::make_shared<ItemPool>();
    SessionModel model("Model", pool);
    model.setUndoRedoEnabled(true);
    EXPECT_EQ(model.undoStack()->index(), 0);
    EXPECT_EQ(model.undoStack()->count(), 0);

    auto dataItem = model.insertItem<Data1DItem>();
    auto graphItem = model.insertItem<GraphItem>();
    graphItem->setDataItem(dataItem);

    auto data_item_identifier = dataItem->identifier();
    auto graph_item_identifier = graphItem->identifier();

    // model has two elements, graph is pointing to the data
    EXPECT_EQ(model.undoStack()->index(), 3);
    EXPECT_EQ(model.undoStack()->count(), 3);
    EXPECT_EQ(model.rootItem()->childrenCount(), 2);
    EXPECT_EQ(graphItem->dataItem(), dataItem);

    // checking pool
    EXPECT_EQ(pool->item_for_key(data_item_identifier), dataItem);
    EXPECT_EQ(pool->item_for_key(graph_item_identifier), graphItem);

    // undoing once (setDataItem operation)
    model.undoStack()->undo();
    EXPECT_EQ(model.undoStack()->index(), 2);
    EXPECT_EQ(model.undoStack()->count(), 3);
    EXPECT_EQ(model.rootItem()->childrenCount(), 2);
    EXPECT_EQ(graphItem->dataItem(), nullptr);

    // undoing two more times item
    model.undoStack()->undo();
    model.undoStack()->undo();
    EXPECT_EQ(model.undoStack()->index(), 0);
    EXPECT_EQ(model.undoStack()->count(), 3);
    EXPECT_EQ(model.rootItem()->childrenCount(), 0);

    // redoing (dataItem is back)
    model.undoStack()->redo();
    EXPECT_EQ(model.undoStack()->index(), 1);
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);
    auto restoredDataItem = model.topItem<Data1DItem>();
    EXPECT_EQ(restoredDataItem->identifier(), data_item_identifier);
    EXPECT_EQ(pool->item_for_key(data_item_identifier), restoredDataItem);

    // redoing (GraphItem) is back
    model.undoStack()->redo();
    EXPECT_EQ(model.undoStack()->index(), 2);
    EXPECT_EQ(model.rootItem()->childrenCount(), 2);
    auto restoredGraphItem = model.topItem<GraphItem>();
    EXPECT_EQ(restoredGraphItem->identifier(), graph_item_identifier);
    EXPECT_EQ(restoredGraphItem->dataItem(), nullptr);

    // redoing (graph is linked with data gaian)
    model.undoStack()->redo();
    EXPECT_EQ(model.undoStack()->index(), 3);
    EXPECT_EQ(model.rootItem()->childrenCount(), 2);
    EXPECT_EQ(restoredGraphItem->dataItem(), restoredDataItem);
}

//! Setup Data1DItem via macro. Undo, then redo.
//! Add GraphItem and Data1DItem, addisgn data to graph, undo, then redo.
//! GraphItem should be pointing again to Data1DItem.
//! This is real bug case.

TEST_F(UndoStackTest, insertDataItemViaMacro)
{
    SessionModel model;
    model.setUndoRedoEnabled(true);
    EXPECT_EQ(model.undoStack()->index(), 0);
    EXPECT_EQ(model.undoStack()->count(), 0);

    // setting up single data item via macro
    model.undoStack()->beginMacro("AddDataItem");
    auto dataItem = model.insertItem<Data1DItem>();
    const std::vector<double> expected_values = {1.0, 2.0, 3.0};
    const std::vector<double> expected_centers = {0.5, 1.5, 2.5};
    dataItem->setAxis<FixedBinAxisItem>(3, 0.0, 3.0);
    dataItem->setValues(expected_values);
    model.undoStack()->endMacro();

    EXPECT_EQ(model.undoStack()->index(), 1);
    EXPECT_EQ(model.undoStack()->count(), 1);

    // undoing and returning back
    model.undoStack()->undo();
    model.undoStack()->redo();
    EXPECT_EQ(model.undoStack()->index(), 1);
    EXPECT_EQ(model.undoStack()->count(), 1);

    auto restoredDataItem = model.topItem<Data1DItem>();
    EXPECT_EQ(restoredDataItem->binCenters(), expected_centers);
    EXPECT_EQ(restoredDataItem->binValues(), expected_values);
}
