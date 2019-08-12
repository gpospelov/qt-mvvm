set(library_name mvvm)

target_sources(${library_name} PRIVATE
    itembackupstrategy.h
    itemcopystrategy.h
    jsonconverterinterfaces.h
    jsonitembackupstrategy.cpp
    jsonitembackupstrategy.h
    jsonitemconverter.cpp
    jsonitemconverter.h
    jsonitemcopystrategy.cpp
    jsonitemcopystrategy.h
    jsonitemdata.cpp
    jsonitemdata.h
    jsonmodel.cpp
    jsonmodel.h
    jsontaginfo.cpp
    jsontaginfo.h
    jsonutils.cpp
    jsonutils.h
    jsonvariant.cpp
    jsonvariant.h
    jsonvariantinterface.h
)

target_include_directories(${library_name} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
