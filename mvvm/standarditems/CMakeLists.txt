set(library_name mvvm)

target_sources(${library_name} PRIVATE
    axesitems.h
    axesitems.cpp
    data1ditem.h
    data1ditem.cpp
    linkeditem.h
    linkeditem.cpp
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
