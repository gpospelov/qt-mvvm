# Example "flateditor".

Example shows how to automatically populate grid layout from 
application model content.

![flateditor](../../doc/flateditor.png)


Application model contains a collection of toy items representing
settings of the neutron beam. The content of the model is shown as a standard tree view on the left part of mainwindow. On the right two widgets are shown:
  
+ Tree like property editor
+ Flat property editor `PropertyFlatView` with grid layout automatically populated from item properties.

Example also demonstrates following features:

## Group property

This is a special object `AngularDistribution` belonging to the `Beam`. It contains a family of predefined probability distributions and their settings.
Property editors shows only currently selected distribution `Gaussian` together with Gaussian settings, hiding other options and their underlying settings.

## Business logic

Item `BeamItem` demonstrates how to implement business logic. Every time the user change beam type using `Type` property, the property `Polarization` of the beam gets either enabled or disabled.
