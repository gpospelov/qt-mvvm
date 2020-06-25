# library: concurrentplotcore
set(library_name concurrentplotcore)

set(CMAKE_AUTOMOC ON)

add_library(${library_name} STATIC "")
target_link_libraries(${library_name} PRIVATE MVVM::View)

target_sources(${library_name} PRIVATE
    graphmodel.cpp
    graphmodel.h
    graphpropertywidget.cpp
    graphpropertywidget.h
    graphwidget.cpp
    graphwidget.h
    graphwidgettoolbar.cpp
    graphwidgettoolbar.h
    jobmanager.cpp
    jobmanager.h
    mainwindow.cpp
    mainwindow.h
    toysimulation.cpp
    toysimulation.h
)

target_include_directories(${library_name} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)

