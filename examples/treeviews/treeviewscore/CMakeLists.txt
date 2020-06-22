set(library_name treeviewscore)

add_library(${library_name} STATIC "")
target_link_libraries(${library_name} PRIVATE mvvm_view)

target_sources(${library_name} PRIVATE
    item_constants.h
    items.cpp
    items.h
    mainwindow.cpp
    mainwindow.h
    samplemodel.cpp
    samplemodel.h
    testwidget.cpp
    testwidget.h
)
