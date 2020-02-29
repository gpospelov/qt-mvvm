# Example "celleditors".

Example shows how to create editable properties and use various editors
in cells of Qt trees and tables.

Application model contains collection of `DemoPropertyItem's`, each having 7 properties of various types. Tree on the left shows application data in the form of
standard two column `name/value` tree. Tree view and table view on the right represent same data, where rows are formed by `DemoPropertyItem's` and columns are made of their properties.

![celleditors](../../doc/celleditors.png)

For the moment following cell editors are supported.

+ Boolean editor with fancy check box.
+ Integer editor as standard QSpinBox with possibility to set limits.
+ Double editor (3 editors are available, have to converge on which one is better).
  + standard QDoubleSpinBox with possibility to set limits.
  + scientific double editor with text-like field.
  + scientific double spin box.
+ Color editor.
+ Combo property editor.
  + as standard QComboBox
  + as QComboBox with checkable fields
+ External property editor

Example also demonstrates following features:

## ExternalProperty

`ExternalProperty` is a special variant carrying the color, the label and string data. It can be used, for example, to call custom external dialog by clicking on cell, containing such variant. Another possible scenario of usage, is to save the identifier of another `SessionItem` inside this property and so provide cross-links
between items and models.
