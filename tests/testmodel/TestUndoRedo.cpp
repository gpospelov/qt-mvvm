// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "toy_includes.h"
#include "toy_items.h"
#include <QUndoStack>
#include <mvvm/model/itemutils.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/model/taginfo.h>

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

//! Undo/redo scenario when few items inserted.

TEST_F(TestUndoRedo, insertParentAndChild)
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

TEST_F(TestUndoRedo, setData)
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

TEST_F(TestUndoRedo, setDataThroughItem)
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
    EXPECT_EQ(item->data(role), value);

    EXPECT_EQ(stack->index(), 2); // insert and setData commands
    EXPECT_FALSE(model.undoStack()->canRedo());
    EXPECT_TRUE(model.undoStack()->canUndo());

    // undoing and checking
    stack->undo();
    EXPECT_EQ(stack->index(), 1);
    EXPECT_FALSE(model.data(item, role).isValid());
}

//! Undo/redo scenario when we set same data. Undo stack should be empty.

TEST_F(TestUndoRedo, setSameData)
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

TEST_F(TestUndoRedo, insertAndSetData)
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

TEST_F(TestUndoRedo, removeRow)
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
    EXPECT_EQ(item->data(role), data);
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

TEST_F(TestUndoRedo, removeParentAndChild)
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

    EXPECT_EQ(parent_at->data(role1), data1);
    EXPECT_EQ(child_at->data(role2), data2);
}

//! Insert item, remove row, undo and check item id.

TEST_F(TestUndoRedo, itemIdentifierOnRemove)
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

TEST_F(TestUndoRedo, multiLayer)
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
    EXPECT_EQ(parent_at->tagOfItem(layer0_at), ToyItems::MultiLayerItem::T_LAYERS);
    EXPECT_EQ(parent_at->tagOfItem(layer1_at), ToyItems::MultiLayerItem::T_LAYERS);
    std::vector<SessionItem*> expected = {layer0_at, layer1_at};
    EXPECT_EQ(parent_at->getItems(ToyItems::MultiLayerItem::T_LAYERS), expected);
}

//! Move single layer from multilayer to another empty multilayer.

TEST_F(TestUndoRedo, moveLayerFromMultiLayer)
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

TEST_F(TestUndoRedo, moveLayerFromMLDeleteSecond)
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

TEST_F(TestUndoRedo, moveLayerFromMLDeleteAll)
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

TEST_F(TestUndoRedo, copyLayerFromMultilayer)
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
    EXPECT_EQ(layer_copy->property(ToyItems::LayerItem::P_THICKNESS).value<double>(),
              expected_thickness);
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
