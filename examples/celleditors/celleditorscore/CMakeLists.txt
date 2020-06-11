# library: celleditorscore
set(library_name celleditorscore)

add_library(${library_name} STATIC "")
target_link_libraries(${library_name} PRIVATE mvvm_viewmodel)

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

