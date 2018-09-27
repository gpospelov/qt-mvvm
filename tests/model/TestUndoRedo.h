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
    model.setUndoRedoEnabled(true);
    auto stack = model.undoStack();

    // initial state of undo redo stack
    EXPECT_TRUE(stack->isActive());
    EXPECT_FALSE(stack->canRedo());
    EXPECT_FALSE(stack->canUndo());
    EXPECT_EQ(stack->index(), 0);
}

TEST_F(TestUndoRedo, setData)
{
    SessionModel model;
    model.setUndoRedoEnabled(true);
    auto stack = model.undoStack();

    // creating item
    auto item = model.insertNewItem();
    EXPECT_FALSE(model.data(item).isValid());

    // setting new data
    QVariant value(42.0);
    model.setData(item, value);
    EXPECT_EQ(model.data(item), value);

    EXPECT_EQ(stack->index(), 1);
    EXPECT_FALSE(model.undoStack()->canRedo());
    EXPECT_TRUE(model.undoStack()->canUndo());

    // undoing and checking
    stack->undo();
    EXPECT_EQ(stack->index(), 0);
    EXPECT_FALSE(model.data(item).isValid());

    // setting data three times
    model.setData(item, QVariant::fromValue(42.0));
    model.setData(item, QVariant::fromValue(43.0));
    model.setData(item, QVariant::fromValue(44.0));
    EXPECT_EQ(stack->index(), 3);
    EXPECT_EQ(model.data(item).toDouble(), 44.0);
    stack->undo();
    stack->undo();
    EXPECT_EQ(model.data(item).toDouble(), 42.0);
    stack->redo();
    stack->redo();
    EXPECT_EQ(model.data(item).toDouble(), 44.0);

}
