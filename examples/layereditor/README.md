# Qt mvvm example: layer editor.

This application represents simplified layer editor for sample construction.

All application data is stored in two independent models: `MaterialModel` for SLD
materials and `SampleModel` for layers and multi-layers.

Each model is represented by two tree views: standard tree with two columns (`property name`
vs `property value`) and custom tree with several columns looking at different parts of
the original model.

User constructs multi-layer with layers in it, define materials and assign materials to the layers.

Example demonstrates:

+ How to implement custom cell editor (material selector).
+ How to create trees with custom layouts which doesn't match the layour of original model.
+ How to serialize model content on disk and load data from it.
+ How to make links between model items (i.e. materials <-> layers) persistent.


