Sample view prototype for BornAgain 2.0.

All application data is stored in two independent models: `MaterialModel` for materials
and `SampleModel` for layers and multi-layers.

Remarks:

+ Separate method to get current root session item from AbstractViewModel would be helpful. Now
  it can be done through sessionItemFromIndex method, but it is rather inobvious.
+ Default tags complicate understanding of the code and later IDE navigation.
+ It is possible to make a simple overload for removing item from the model, like
  SessionModel::removeItem(SessionItem* item)
+ It would be convenient to have some sort of PlaceholderViewItem, which holds a pointer
  to a session item, but otherwise behaves exactly like a QStandardItem
+ allow overloading SessionModel::insertNewItem in the descendant classes
+ replace CustomEditor and CustomEditor factory with standard Qt factory. The latter can handle
  any QWidget as an editor (which is definitely a plus). Further customization of the editors
  can be done through QStyledItemDelegate::createEditor overloads.
+ CellDecorationInterface and its usage in ViewModelDelegate::paint can be done differently:
  see CellDecoratorInterface and SampleViewDelegate::initStyleOption in sampleview.
+ SessionModel::createCopy copies an item, but there is no obvious way to insert an existing item
  into a session model. I would even prefer to have the copy method (aka clone)
  in the SessionItem class.

Required fixes/features (sampleview):

+ MaterialEditor: Make MaterialControlPanel buttons show borders on cursor above.
+ MaterialEditor: Hold check and color box columns sizes minimal
+ MaterialEditor: Govering checkbox to select/deselect all materials
+ MaterialEditor: Additional column to choose material type?
+ MaterialEditor: Button to hide columns
+ MaterialEditor: Centering checkboxes and pixmaps
+ MaterialEditor: Allow sorting by material name
+ MaterialEditor: Tooltips on control panel
+ Automatically select all the text in ScientificSpinBox on focus-in event.
+ Setting limits and step for ScientificSpinBox as an editor in SampleViewDelegate
