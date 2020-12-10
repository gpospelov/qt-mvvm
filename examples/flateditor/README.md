# Example "flateditor".

The example shows how to automatically populate the grid layout from the
application model content.

![flateditor](../../doc/assets/flateditor.png)


Application model contains a collection of toy items representing settings of
the neutron beam. The content of the model is shown as a standard tree view on
the left part of main window. On the right two widgets are shown:
  
+ Tree-like property editor
+ Flat property editor `PropertyFlatView` with grid layout automatically
  populated from item properties.

The example also demonstrates the following features:

## Group property

This is a special object `AngularDistribution` belonging to the `Beam`. It
contains a family of predefined probability distributions and their settings.
Property editors show only currently selected distribution `Gaussian` together
with Gaussian settings, hiding other options and their underlying settings.

## Business logic

Item `BeamItem` demonstrates how to implement business logic. Every time the
user change beam type using `Type` property, the property `Polarization` of the
beam gets either enabled or disabled.
