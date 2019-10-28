Sample view prototype for BornAgain 2.0.

All application data is stored in two independent models: `MaterialModel` for materials
and `SampleModel` for layers and multi-layers.

Remarks:

+ Separate method to get current root session item from AbstractViewModel would be helpful. Now
  it can be done through sessionItemFromIndex method, but it is rather inobvious.
+ It would be convenient to have some sort of PlaceholderViewItem, which holds a pointer
  to a session item, but otherwise behaves exactly like a QStandardItem
+ allow overloading SessionModel::insertNewItem in the descendant classes
+ replace CustomEditor and CustomEditor factory with standard Qt factory. The latter can handle
  any QWidget as an editor (which is definitely a plus). Further customization of the editors
  can be done through QStyledItemDelegate::createEditor overloads.
+ CellDecorationInterface and its usage in ViewModelDelegate::paint can be done differently:
  see CellDecoratorInterface and SampleViewDelegate::initStyleOption in sampleview.

Required fixes/features (sampleview):

+ MaterialEditor: Make MaterialControlPanel buttons show borders on cursor above.
+ MaterialEditor: Hold check and color box columns sizes minimal
+ MaterialEditor: Govering checkbox to select/deselect all materials
+ MaterialEditor: Additional column to choose material type?
+ MaterialEditor: Button to hide columns
+ MaterialEditor: Centering checkboxes and pixmaps
+ MaterialEditor: Allow sorting by material name
+ MaterialEditor: Tooltips on control panel
+ MaterialEditor: color editor is not opened on double click (win, qt 5.12.0)
+ MaterialEditor: forbid editing checkbox on double click (win, qt 5.12.0)
+ SampleDesigner: replace QGraphicObject with QGraphicItem as the base class
  for ConnectableView and move all signals/slots to a separate controller.
+ SampleDesigner: replace the messy way of assigning material name to layers.
+ SampleDesigner: enable scroll-rescaling
+ SampleDesigner: move SceneModelController and SceneSelectionController out of DesignerScene
+ SampleEditor: improve drag-n-drop or remove it completely. Improvement will require inheriting
  QTreeView.
+ SampleEditor: implement tab-based editing like in MaterialEditor.
+ SampleEditor: provide only the materials available from the MaterialEditor
+ SampleEditor: add icons for (multi)layer insertion.
+ SampleEditor/MaterialEditor: enable post-button press selection. Requires focus return to
  the corresponding table/tree view.
+ Automatically select all the text in ScientificSpinBox on focus-in event.
+ Setting limits and step for ScientificSpinBox as an editor in SampleViewDelegate
+ Find the canonical way to initialize qrc files in a library
