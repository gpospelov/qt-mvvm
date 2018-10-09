# Requirements

List of technical requirements for BornAgain main application refactoring.
See bornagainproject.org

+ SessionItem and SessionModel should be free of Qt classes
+ Unddo/redo
+ SessionItem should have persistent link to be able to find it in the model after project restore
+ Serialization based on json and not xml
+ Every SessionItem should be able to save non-xml data
+ Project file back compatibility


+ Alternative to item tag?
+ SessionItemData of SessionItem shold be recorded uniformly (all limits, displayRoles, etc)
+ Business logic of SessionItem should be invoked outside of constructor
+ Buisiness logic shouldn't be invoked during item clone
+ Problem of DistributionItem

+ Provide copying of SessionItem containing non-xml data

## RealTimeView

+ Should contain materials to tune
+ Should be possible to tune integeres

## Projections

+ Possibility to have projections integrated along some band
