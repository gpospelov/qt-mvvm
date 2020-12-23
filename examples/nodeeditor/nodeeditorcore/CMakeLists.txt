set(library_name nodeeditorcore)

set(CMAKE_AUTOMOC ON)

add_library(${library_name} STATIC "")
target_link_libraries(${library_name} PRIVATE MVVM::View)

target_sources(${library_name} PRIVATE
    mainwindow.cpp
    mainwindow.h
    modeleditorwidget.cpp
    modeleditorwidget.h
    samplemodel.cpp
    samplemodel.h
)

