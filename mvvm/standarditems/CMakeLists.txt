set(library_name mvvm)

target_sources(${library_name} PRIVATE
    axisitems.h
    axisitems.cpp
    data1ditem.h
    data1ditem.cpp
    graphitem.h
    graphitem.cpp
    graphviewportitem.h
    graphviewportitem.cpp
    linkeditem.h
    linkeditem.cpp
    plottableitems.h
    plottableitems.cpp
    standarditemcatalogue.cpp
    standarditemcatalogue.h
    vectoritem.cpp
    vectoritem.h
)

target_include_directories(${library_name}
    PUBLIC
        $<INSTALL_INTERFACE:public>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)
