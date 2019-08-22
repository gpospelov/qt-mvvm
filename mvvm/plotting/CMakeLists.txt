set(library_name mvvm)

target_sources(${library_name} PRIVATE
    customgraphwidget.h
    customgraphwidget.cpp
    axesplotcontroller.h
    axesplotcontroller.cpp
    itemcontroller.h
    itemcontroller.cpp
)

target_include_directories(${library_name}
    PUBLIC
        $<INSTALL_INTERFACE:public>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)
