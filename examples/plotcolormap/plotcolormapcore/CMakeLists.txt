# library: plotcolormapcore
set(library_name plotcolormapcore)

set(CMAKE_AUTOMOC ON)

add_library(${library_name} STATIC "")
target_link_libraries(${library_name} PRIVATE MVVM::View)

target_sources(${library_name} PRIVATE
    colormapmodel.cpp
    colormapmodel.h
    colormappropertywidget.cpp
    colormappropertywidget.h
    colormapwidget.cpp
    colormapwidget.h
    mainwindow.cpp
    mainwindow.h
)

target_include_directories(${library_name} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/..)
