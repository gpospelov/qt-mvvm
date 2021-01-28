# Example "collidingmice".

The example shows how to modify the third-party application to provide serialization, undo-redo, and proper model-view relations.

If you are familiar with Qt's reach example section you might
saw it's funny `collidingmice` example showing basics of
`QGraphicsScene`.

![colliding-mice-before](../../doc/assets/colliding-mice-before.png)

To demonstrate the idea behind `qt-mvvm` library the code of the example was 
slightly modified. The mice data has been moved into the dedicated model, 
the content of the model was shown both in the `QGraphicsScene` and in `QTreeView`. 
It is possible now to save the application state in json file and later load 
the session back with saved mice positions. Additionally, it is possible to go 
back in time and watch how mice are moving in opposite directions by dragging a 
slider:

![colliding-mice-after](../../doc/assets/colliding-mice-after.png)

See short animation [here](../../doc/assets/colliding-mice.gif).

The demo shows that `qt-mvvm` library allows 
to equip the GUI with the serialization and undo/redo and to provide proper 
model/view relations via relatively small modifications to the original code.
Implementing similar features from the scratch in bare metal Qt would take
much more time and the resulting code wouldn't be easily transferable to another project.

