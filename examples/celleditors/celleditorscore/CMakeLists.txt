# library: celleditorscore
set(library_name celleditorscore)

set(CMAKE_AUTOMOC ON)

add_library(${library_name} SHARED "")
target_link_libraries(${library_name} PRIVATE MVVM::View)

target_sources(${library_name} PRIVATE
    item_constants.h
    items.cpp
    items.h
    mainwindow.cpp
    mainwindow.h
    modeleditorwidget.cpp
    modeleditorwidget.h
    samplemodel.cpp
    samplemodel.h
)

