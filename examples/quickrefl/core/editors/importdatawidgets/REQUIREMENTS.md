# The data loader requirements.


This is the list of minimal requirements for
the reflectometry data loader. Please keep in mind,
that there is an ongoing discussion in the reflectometry community about common
software for data reduction, common data format, "order of columns", etc. While we are waiting on the practical outcome of this discussion, we must proceed basing on our general sense of what is rational and beautiful.

Our task is to provide the data loader with clean and extendable design,
a reasonable minimum of functionality, not too many bells-and-whistles, and then simply follow user requests.

<hr>

## User story (the big picture).

+ User opens an ASCII file containing multi-column reflectometry data.
+ Whole data is loaded to the Qt table.
+ It is unkown in advance which column contains what.
  + Nevertheless, it is probable that first column contains Q in angstroms, second column R, the third column sigma(R).
  + The data is so-called point-wise data.
+ The user defines what will be on X-axis.
  + Which column index to use as data source.
  + What will be there (Q in nm, Q in angstrom, in degrees, etc).
+ Similarly, the user defines Y axis.
+ Similarly, the user defines Y axis uncertanties.
+ User pushes the button "Load". The data appears in the form of graph.

<hr>

## Three main components.

We idenitfy three well isolated components of the data loader:

1. Data importer
   + Imports multi-column data from ASCII file to QTableWidget.
2. Data configuration.
   + Creates a data structure vector(Q, R, dR) with the results of reflectometry measurements using the data from the table.
   + Imports the data to qt-mvvm in the form of GraphItem's.
3. Data viewer.
   + Provides navigation through loaded datasets, combining graphs on same viewport, changing legends and titles, etc.

<hr>

### 1. Data importer.

The task is to load the ASCII file to QTableWidget.
Here we can benefit from successful UI tricks invented by Exel, Libreoffice, and Origin.

**features:**

+ Distinguish ASCII files from binary files.
+ Load multi-column data using `[spaces]` as default separator. 
+ Skip comment line using `#` as comment line identifier.
+ Provide basic sanity checks.
  + Columns of different length.
  + Data of different type in columns.
+ The multi-column data has to be loaded in QTableWidget based on QStandardItemModel (no qt-mvvm involved).
+ Make sure that large files are loaded fast enough.

**advanced features:**

+ Guess if it is binary file by reading few first bytes.
+ Guess common separator by reading first bytes of data.
+ Guess comment line identifier.
+ Guess number of columns by reading first bytes of data. 
+ Provide possibility to define column separator, comment line identifier.

<hr>

### 2. Data configuration.

At this point we have a table with multiple columns opened in a widget. 
The user defines which columns represents x-axis, y-axis and y-axis uncertanties using combo boxes.
 
```
X-axis:  combo_for_column_index   combo_to_select_xType
Y-axis:  combo_for_column_index   combo_to_select_yType
Y-error: combo_for_column_index   combo_to_select_yerrType
```


 **features:**

 + Results of the selection is saved in application's QSettings.
 + Previous QSettings should be applied to default selection.
 + Where must be the way to upload several data sources at once, using same selections.

<hr>

3. Data viewer.

+ In general, it should be like QTreeView on the left, and GraphCanvas on the right.
+ Tree view should contain top level items: viewports and graphs, belonging to them.
+ There should be possible to drag-and-drop graphs inside the tree: from one viewports to another.
+ When we are clicking on viewport item on the left, the canvas on the right shows cviewport with orresponding graphs.
+ When we click on single graph on the left, we see single graph on it's viewport on the right. Other graphs belonging to same viwport are hidden.


  