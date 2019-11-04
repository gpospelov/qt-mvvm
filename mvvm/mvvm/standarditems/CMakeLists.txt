set(library_name mvvm)

target_sources(${library_name} PRIVATE
    axisitems.cpp
    axisitems.h
    colormapitem.cpp
    colormapitem.h
    colormapviewportitem.cpp
    colormapviewportitem.h
    containeritem.cpp
    containeritem.h
    data1ditem.cpp
    data1ditem.h
    data2ditem.cpp
    data2ditem.h
    graphitem.cpp
    graphitem.h
    graphviewportitem.cpp
    graphviewportitem.h
    linkeditem.cpp
    linkeditem.h
    plottableitems.cpp
    plottableitems.h
    standarditemcatalogue.cpp
    standarditemcatalogue.h
    vectoritem.cpp
    vectoritem.h
    viewportitem.cpp
    viewportitem.h
)

target_include_directories(${library_name}
    PUBLIC
        $<INSTALL_INTERFACE:public>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)
