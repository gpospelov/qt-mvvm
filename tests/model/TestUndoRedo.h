#include <gtest/gtest.h>
#include "sessionmodel.h"
#include "sessionitem.h"
#include <QUndoStack>

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
    auto child0 = model.insertNewItem("Layer0", parent);
    auto child1 = model.insertNewItem("Layer1", parent);

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

    const int role = Qt::DisplayRole;
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

//! Checks if we insert item, set data and undo everything we can get back to the data.

TEST_F(TestUndoRedo, insertAndSetData)
{
    const model_type modelType("abc");

    const int role = Qt::DisplayRole;
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
