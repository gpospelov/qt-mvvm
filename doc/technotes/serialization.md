# Tech notes about serialization

Serialization is involved in the following scenarios:

## ItemBackupStrategy within RemoveItemCommand

This is the part of the undo/redo framework: the item, which has been deleted, has to be reconstructed, if necessary. Two approaches are possible:

A. The whole item state has to be serialized to JSON. Later on, the item has to be fully
reconstructed from JSON. The resulting `SessionItem` has to be exactly the same
(type, data role, tooltips, children) as before.

+ we are sure that the restored item will be identical (+)
+ we unnecessarily serialize content which is unlikely to change (e.g. tooltips)  (-)

B. Only essential data is serialized (`DATA` role, the content of universal tags).
Here we assume, that tooltips and property tags exist already, as they were created
via `SessionItem`'s constructor.

+ we do not serialize content which is unlikely to change (tooltips)  (+)
+ same algorithm can be used for save/load (see below) (+)

## ItemCopyStrategy within CopyItemCommand

Same as above, except identifier: copied item mush have new identifier.

## Project save/load

`Project` save/load is done using `JsonModelConverter`. The result
of saving is the appearance on disk JSON files with the model content.
Loading of the project leads to clearance of the content of given model and its rebuild from
the JSON content.

Only essential data (as in approach `B` above), has to be serialized.
Special attention should be paid to project file back compatibility.
Here the typical situation is the following: JSON content on disk has data roles and
registered tags that are different from whose existing at run time. This situation
can happen when we load the old project.

The following rules should be applied:

+ tags in JSON should match tags existing at runtime
  + runtime can have other tags registered
  + if JSON contains tags non-existing at runtime, they should be skipped
+ data roles on JSON should match roles existing at runtime
  + for the moment we will write and read roles: DATA and IDENTIFIER
  + all unknown data roles in JSON should be ignored
  + all known roles in JSON should be taken, runtime values overwritten.
  + runtime can have more data roles, than in JSON (i.e. TOOLTIPS)

## Current conventions

```C++
class SomeItem {
    addProperty("Correlation", 0.5)
    addProperty<VectorItem>("Position")
    registerTag("Children", UniversalTag);
}
```

+ Use same serialization mechanism for undo/redo and save/load
+ Rely on tags as they have been created in the constructor
  + In given example we have two property tags and one universal tag
+ Reuse runtime items in  property tags
+ Require that universal tags are empty, and fully rebuild its content from JSON
+ 


