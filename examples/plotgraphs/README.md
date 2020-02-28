# Example "plotgraphs".

Example shows how to plot one-dimensional graphs using wrappers around `qcustomplot` library. 

![plotgraphs](../../doc/plotgraphs.png)

Application model contains collection of various items to 
properly separate `scientific data` from `presentation data`. 

## Data1DItem

It's an item to hold one-dimensional vector of `double` values and information
about axis binning. `Data1DItem` is not intended for direct plotting and needs `GraphItem` for that.

## GraphItem

It's an item which contains a link to certain `Data1DItem` and serves as a wrapper around scientific data. Its main purpose is to carry the additional data for presentation purposes: the title of the graph, color of the line etc. `GraphItem` is not intended for direct plotting and needs `GraphViewportItem` for that.

## GraphViewportItem

It's an item which can have arbitrary amount of `GraphItem's` on board. Additionally it contains items to store the data related to viewport axes: current zoom level, axis title etc. `GraphViewportItem` needs `GraphCanvas` for plotting.

## GraphCanvas

It is a widget, wrapper around `QCustomPlot`, provided with status string.
It shows the content of `GraphViewportItem` on the screen and establishes the signaling between `QCustomPlot` and `SessionModel`.
When user zooms in into `QCustomPlot` with the mouse wheel, the data of the model is updated. If the user then saves a project file, all zoom level's will be automatically preserved.

