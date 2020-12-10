# library: flateditorcore
set(library_name flateditorcore)

set(CMAKE_AUTOMOC ON)

add_library(${library_name} STATIC "")
target_link_libraries(${library_name} PRIVATE MVVM::View)

target_sources(${library_name} PRIVATE
    demowidget.cpp
    demowidget.h
    mainwindow.cpp
    mainwindow.h
    sampleitems.cpp
    sampleitems.h
    samplemodel.cpp
    samplemodel.h
)
