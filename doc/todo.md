# TODO list

## SessionModel

+ Add tolltips role to SessionItem.
+ Add isVisible property to SessionItem.
+ Get rid of SessionItem::SetDataIntern.
+ Implement SessionItem::clone
+ Implement SessionModel::clone
+ Implement item move from one parent to another.


## Undo/redo

+ Remove access to ItemManager from all commands (switch to creator functions aka CommandContext).
+ Wrap QUndoStack to hide Qt's origin.
+ Move commands to separate directories.
+ Switch to ItemBackupStrategy.


## ViewModel

+ Prevent autoclose in spin boxes while clicking on top/down arrow (celleditor example).
+ Implement switch to the next cell editor on tab-press-key-event.
+ Implement spinbox-and-slider double cell editor.
+ Implement combo property editor with check boxes.
+ Refactor AbstractViewModelController.
  + Remove friendship between AbstractViewModel and AbstractViewModelController.
  + Remove one of ::findViews from AbstractViewModel.
  + Think of pure virtual ViewModelInterface.
  + Think of ViewModelAdapter with multiple inheritance: ViewModelInterface and QStandardViewModel.


## Serialization

+ Rename all Json* family to JsonConverter* family.
+ Hide all Qt's json objects behind JsonItem.
+ Implement ProjectDocument and hide inside read/write of json to file for ApplicationModels.


## User examples

+ Add demo for all possible editors in `celleditors` example.
+ Implement drag-and-drop case for `layereditor` example.


## Miscellaneous

+ Introduce common style of comments in all headers.
+ Check json performance on large data.
+ Implement tech model showing bare json content.


## General & Big

+ Implement Travis and Appveyor continuous integration.
+ Implement universal flat editor.
+ Implement Data1DItem, Data2DItem, Data1DPresenterItem, Data2DPresenterItem.
  + Implement qcustom plot based example for plotting
+ Implement SessionItemWidget equivalent.
+ Refactor CMake machinery in the part of public/private interface.
+ Implement back compatibility system.
  + Logger to report errors from json converters.
  + Test case demonstrating reading obsolete project files.


<hr>
