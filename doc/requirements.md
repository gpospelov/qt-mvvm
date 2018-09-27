# Requirements

List of technical requirements for BornAgain main application refactoring.
See bornagainproject.org

+ SessionItem and SessionModel should be free of Qt classes
+ Unddo/redo
+ SessionItem should have persistent link to be able to find it in the model after project restore
+ Serialization based on json and not xml
+ Every SessionItem should be able to save non-xml data
+ Project file back compatibility




