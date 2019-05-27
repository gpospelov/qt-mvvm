# Qt mvvm example: cell editors.

Example shows how to create editable properties and use various editors
in cells of Qt trees and tables.

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
