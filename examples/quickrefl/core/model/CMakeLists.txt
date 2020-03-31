# Static library: quickreflcore.

target_sources(quickreflcore PRIVATE
    applicationmodels.cpp
    applicationmodels.h
    item_constants.h
    jobitem.cpp
    jobitem.h
    jobmodel.cpp
    jobmodel.h
    layeritems.cpp
    layeritems.h
    materialitems.cpp
    materialitems.h
    materialmodel.cpp
    materialmodel.h
    materialpropertycontroller.cpp
    materialpropertycontroller.h
    samplemodel.cpp
    samplemodel.h
)

target_include_directories(quickreflcore PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
