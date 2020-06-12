# Example "saveloadproject".

The example shows how to save/load projects on disk.
The project is a collection of `json` files representing application models in a folder on disk.

In this example, we demonstrate, how to handle usual activity related to the
creation of a new project or opening an existing one.
Standard scenarios are taken care of:

+ User starts an application, modifies the content, then decides to close it without saving.
+ User opens the project from the list of the existing ones.
+ User saves the project under a different name.
+ User tries to create a new project while having unsaved changes.

And many other similar combinations.
Application tracks the list of recent projects and last selected directory in QSettings.


