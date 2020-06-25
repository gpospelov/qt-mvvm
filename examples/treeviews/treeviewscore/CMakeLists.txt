set(library_name treeviewscore)

set(CMAKE_AUTOMOC ON)

add_library(${library_name} STATIC "")
target_link_libraries(${library_name} PRIVATE MVVM::View)

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
