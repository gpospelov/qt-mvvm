# library: dragandmovecore
set(library_name dragandmovecore)

add_library(${library_name} STATIC "")
target_link_libraries(${library_name} PRIVATE mvvm_view)

target_sources(${library_name} PRIVATE
    containereditorwidget.cpp
    containereditorwidget.h
    dragviewmodel.cpp
    dragviewmodel.h
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

