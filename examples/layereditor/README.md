# Example "layereditor".

The example demonstrates how to create a tree with a custom layout.

This application represents a simplified multi-layer editor, where the user
defines materials, their scattering properties and assembles multi-layer system
made of different materials.

All application data is stored in two independent models: `MaterialModel` for
materials and `SampleModel` for layers and multi-layers.

![layereditor](../../doc/assets/layereditor.png)

Each model is represented by two tree views: a standard tree with two columns
(`property name` and `property value`) and custom tree with several columns
looking at different parts of the original model.

Example demonstrates:

+ How to implement a custom cell editor (material selector).
+ How to create a tree with a custom layout which differs from the layout of the
  original model.
+ How to make links between items belonging to two different models (i.e.
  materials .vs. layers).
+ How to write controllers that propagates notifications from one model to
  another model.
  +  For example, editing material color in one model will change the color of
     the label in another model.
+ How to save application models on disk and load it after.
  + By selecting `File` menu it is possible to save everything in JSON and
    restore it after. All links between items (i.e. correspondence of materials
    to layers) will be preserved.
  


