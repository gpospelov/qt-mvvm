#include "google_test.h"
#include "sessionmodel.h"
#include "sessionitem.h"
#include <QUndoStack>

using namespace ModelView;

class TestUndoRedo : public ::testing::Test
{
public:
    ~TestUndoRedo();
};

TestUndoRedo::~TestUndoRedo() = default;

TEST_F(TestUndoRedo, initialState)
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

TEST_F(TestUndoRedo, insertNewItem)
{
    const model_type modelType("MultiLayer");
    SessionModel model;
    model.setUndoRedoEnabled(true);
    auto stack = model.undoStack();

    // inserting single item
    auto item = model.insertNewItem(modelType);
    EXPECT_TRUE(item != nullptr);
    EXPECT_EQ(item->modelType(), modelType);
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
    EXPECT_EQ(model.rootItem()->childAt(0)->modelType(), modelType);
    EXPECT_EQ(stack->index(), 1);
    EXPECT_FALSE(stack->canRedo());
    EXPECT_TRUE(stack->canUndo());

    // clearing stack
    stack->clear();
    EXPECT_EQ(stack->index(), 0);
    EXPECT_FALSE(stack->canRedo());
    EXPECT_FALSE(stack->canUndo());
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);
    EXPECT_EQ(model.rootItem()->childAt(0)->modelType(), modelType);
}

//! Undo/redo scenario when few items inserted.

TEST_F(TestUndoRedo, insertParentAndChild)
{
    SessionModel model;
    model.setUndoRedoEnabled(true);
    auto stack = model.undoStack();

    auto parent = model.insertNewItem("MultiLayer1");
    model.insertNewItem("Layer0", parent);
    model.insertNewItem("Layer1", parent);

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
    EXPECT_EQ(parent->childAt(0)->modelType(), "Layer0");
}

//! Undo/redo scenario when item inserted and data set few times.

TEST_F(TestUndoRedo, setData)
{
    const model_type modelType("abc");

    const int role = ItemDataRole::DATA;
    SessionModel model;
    model.setUndoRedoEnabled(true);
    auto stack = model.undoStack();

    // creating item
    auto item = model.insertNewItem(modelType);
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
    EXPECT_EQ(model.data(item, role).toDouble(), 44.0);
    stack->undo();
    stack->undo();
    EXPECT_EQ(model.data(item, role).toDouble(), 42.0);
    stack->redo();
    stack->redo();
    EXPECT_EQ(model.data(item, role).toDouble(), 44.0);
}

//! Undo/redo scenario when item data changed thourgh item and not the model.

TEST_F(TestUndoRedo, setDataThroughItem)
{
    const int role = ItemDataRole::DATA;
    const QVariant value(42.0);

    SessionModel model;
    model.setUndoRedoEnabled(true);
    auto stack = model.undoStack();

    // creating item
    auto item = model.insertNewItem("Layer");
    EXPECT_FALSE(model.data(item, role).isValid());

    // setting new data through item (and not through model)
    item->setData(value, role);
    EXPECT_EQ(item->data(role), value);

    EXPECT_EQ(stack->index(), 2); // insert and setData commands
    EXPECT_FALSE(model.undoStack()->canRedo());
    EXPECT_TRUE(model.undoStack()->canUndo());

    // undoing and checking
    stack->undo();
    EXPECT_EQ(stack->index(), 1);
    EXPECT_FALSE(model.data(item, role).isValid());
}

//! Checks if we insert item, set data and undo everything we can get back to the data.

TEST_F(TestUndoRedo, insertAndSetData)
{
    const model_type modelType("abc");

    const int role = ItemDataRole::DATA;
    SessionModel model;
    model.setUndoRedoEnabled(true);
    auto stack = model.undoStack();

    // creating item
    auto item = model.insertNewItem(modelType);
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
    item = model.rootItem()->childAt(0);
    EXPECT_EQ(model.data(item, role).toDouble(), 42.0);
}

//! Inserting item, setting the data, removing row, undoing, checking item and data.

TEST_F(TestUndoRedo, removeRow)
{
    const int role = ItemDataRole::DATA;
    const QVariant data(42);

    SessionModel model;
    model.setUndoRedoEnabled(true);
    auto stack = model.undoStack();

    auto item = model.insertNewItem("MultiLayer");
    item->setData(data, role);

    // initial state before removing the row
    EXPECT_EQ(stack->count(), 2); // insert and setData commands
    EXPECT_EQ(stack->index(), 2); // insert and setData commands
    EXPECT_FALSE(model.undoStack()->canRedo());
    EXPECT_TRUE(model.undoStack()->canUndo());
    EXPECT_EQ(item->data(role), data);
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);

    // removing the row
    model.removeRow(model.rootItem(), 0);
    EXPECT_EQ(stack->count(), 3);
    EXPECT_EQ(stack->index(), 3);
    EXPECT_EQ(model.rootItem()->childrenCount(), 0);

    // undoing and checking the data
    stack->undo();
    EXPECT_EQ(stack->count(), 3);
    EXPECT_EQ(stack->index(), 2);
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);
    item = model.rootItem()->childAt(0);
    EXPECT_EQ(model.data(item, role).toDouble(), 42.0);
    EXPECT_EQ(item->modelType(), "MultiLayer");
}

//! Inserting parent and child, setting data to them, removing parent, undoing and checking.

TEST_F(TestUndoRedo, removeParentAndChild)
{
    const int role1(ItemDataRole::DATA), role2(ItemDataRole::DISPLAY);
    const QVariant data1(42), data2(43);

    SessionModel model;
    model.setUndoRedoEnabled(true);
    auto stack = model.undoStack();

    auto parent = model.insertNewItem("MultiLayer");
    parent->setData(data1, role1);
    auto child = model.insertNewItem("Layer", parent);
    child->setData(data2, role2);

    EXPECT_EQ(stack->count(), 4);
    EXPECT_EQ(stack->index(), 4);

    // removing parent
    model.removeRow(model.rootItem(), 0);
    EXPECT_EQ(stack->count(), 5);
    EXPECT_EQ(stack->index(), 5);
    EXPECT_EQ(model.rootItem()->childrenCount(), 0);

    // undoing
    stack->undo();
    EXPECT_EQ(stack->count(), 5);
    EXPECT_EQ(stack->index(), 4);
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);
    parent = model.rootItem()->childAt(0);
    child = parent->childAt(0);

    EXPECT_EQ(parent->modelType(), "MultiLayer");
    EXPECT_EQ(child->modelType(), "Layer");

    EXPECT_EQ(parent->data(role1), data1);
    EXPECT_EQ(child->data(role2), data2);
}

//! Insert item, remove row, undo and check item id.

TEST_F(TestUndoRedo, itemIdentifierOnRemove)
{

    SessionModel model;
    model.setUndoRedoEnabled(true);
    auto stack = model.undoStack();

    auto parent = model.insertNewItem("MultiLayer");
    identifier_type parent_id = parent->data(ItemDataRole::IDENTIFIER).value<std::string>();
    auto child = model.insertNewItem("Layer", parent);
    identifier_type child_id = child->data(ItemDataRole::IDENTIFIER).value<std::string>();

    // removing parent
    model.removeRow(model.rootItem(), 0);
    EXPECT_EQ(stack->count(), 3);
    EXPECT_EQ(stack->index(), 3);
    EXPECT_EQ(model.rootItem()->childrenCount(), 0);

    stack->undo();
    parent = model.rootItem()->childAt(0);
    child = parent->childAt(0);
    identifier_type parent_id2 = parent->data(ItemDataRole::IDENTIFIER).value<std::string>();
    identifier_type child_id2 = child->data(ItemDataRole::IDENTIFIER).value<std::string>();

    EXPECT_EQ(parent_id, parent_id2);
    EXPECT_EQ(child_id, child_id2);
}
