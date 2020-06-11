# library: flateditorcore
set(library_name flateditorcore)

add_library(${library_name} STATIC "")
target_link_libraries(${library_name} PRIVATE mvvm_viewmodel)

target_sources(${library_name} PRIVATE
    demowidget.cpp
    demowidget.h
    items.cpp
    items.h
    mainwindow.cpp
    mainwindow.h
    samplemodel.cpp
    samplemodel.h
)

target_include_directories(${library_name} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
