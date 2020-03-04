# TODO list

## SessionModel

+ Add tolltips role to SessionItem.
+ Add isVisible property to SessionItem.
+ Get rid of SessionItem::SetDataIntern.
+ Implement SessionItem::clone
+ Implement SessionModel::clone
+ Implement EditorType role.
+ Get rid from QColor.

## Undo/redo

+ Wrap QUndoStack to hide Qt's origin.

## ViewModel

+ Prevent autoclose in spin boxes while clicking on top/down arrow (celleditor example).
+ Implement switch to the next cell editor on tab-press-key-event.
+ Implement spinbox-and-slider double cell editor.
+ Implement combo property editor with check boxes.

## Serialization

+ Rename all Json* family to JsonConverter* family.
+ Hide all Qt's json objects behind JsonItem.

## User examples

+ Repair flateditor example.
+ Profile collidingmice example.
+ Make QML example.

## Miscellaneous

+ Check json performance on large data.
+ Implement tech model showing bare json content.
+ Implement code test coverage.
+ Switch to GitHub action from Travis and Appveyor.
+ Provide machinery for performance measurements in unit tests.
+ Refactor ItemMapper to use new Signal library.

## General & Big

+ Implement universal flat editor.
+ Implement proper CMake install.
+ Implement back compatibility system.
  + Logger to report errors from json converters.
  + Test case demonstrating reading obsolete project files.

