# Undo/redo design

Here we explain techical details behind undo/redo framework. Method's signatures are simplified
(no tag machinery presented) to make it easier to understand the whole thing.

### SessionItem interface

> Everything which goes through SessionItem doesn't appear in undo/redo.

```
bool setData(variant, role)
bool insertItem(SessionItem* child, int row)
SessionItem* takeItem(int row)
```

### SessionModel interface

> Everything which goes through SessionModel can be undone and redone again.
> All interface methods of SessionModel to insert/remove items are done through Command pattern.

<hr>

#### Setting data

```
bool setData(SessionItem* item, variant new_data, int role)
```

+ **Preparation** 
  + save path(item), new_data, role
+ **Execute**
  + item = find(path)
  + old_data = item->data()
  + item->setData(new_data)
  + new_data = old_data
+ **Undo**
  + does exactly the same as **Execute**

<hr>

#### Inserting new item

```
SessionItem* insertNewItem(model_type, SessionItem* parent, row)
```

+ **Preparation** 
  + save model_type, path(parent), row
+ **Execute**
  + parent = find(path)
  + child = new Item(model_type)
  + parent->insertItem(child)
+ **Unddo**
  + parent = find(path)
  + parent->takeItem(row)
  + delete child;

> Every consequitive pair of execute/undo will generate items with new identifiers and new
> item pointers. Potentially it can cause problems if user relies on item's pointers and doesn't
> trace item destruction.

<hr>

#### Removing item

```
bool removeItem(SessionItem* parent, row)
```

+ **Preparation**
  + save path(parent), row
+ **Execute**
  + child -> json-exact-copy
  + parent = find(path)
  + parent->takeItem(child)
  + delete child
+ **Undo**
  + parent = find(path)
  + json-exact-copy -> child (identifiers kept)
  + parent->insertItem(child, row)

<hr>

#### Moving item

```
bool moveItem(SessionItem* child, SessionItem* new_parent, int new_row)
```

> Moving is possible only between items belonging to the same model.
> Reason: it is impossible to provide consistent undo/redo between two models in that case.
> Use copyItem if you need to populate the model with items from another model.

+ **Preparation**
  + save path(child->parent), path(new_parent), new_row
+ **Execute**
  + original_parent = find(path_of_original)
  + new_parent = find(path_of_new_parent)
  + child = original_parent->takeItem()
  + new_parent->insertItem(child)
  + save path(original_parent), path(new_parent)
+ Undo
  + new_parent = find(path_of_new_parent)
  + original_parent = find(path_of_original)
  + child = new_parent->takeItem
  + original_parent->insertItem(child)
  + save path(original_parent), path(new_parent)

> Return value of moveItem command is a bit of fake. It is complicated to make consistent undo/redo
> when either removing or inserting item has failed.

<hr>

#### Copying item

```
SessionItem* copyItem(const SessionItem* child, SessionItem* new_parent, int row)
```

> Item to copy may belong to any model, or be outside of any model.

+ **Preparation**
  + child -> json-exact-copy -> new child-with-new-ids
  + child-with-new-ids -> json-exact-copy
  + save path(new_parent), row
+ **Execute**
  + new_parent = find(path_new_parent)
  + json-exact-copy -> child (identifiers kept)
  + new_parent->insertItem(child)
+ **Undo**
  + new_parent = find(path_new_parent)
  + delete new_parent->takeItem(row)
