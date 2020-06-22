# library: plotgraphscore
set(library_name plotgraphscore)

add_library(${library_name} STATIC "")
target_link_libraries(${library_name} PRIVATE mvvm_view)

target_sources(${library_name} PRIVATE
    graphmodel.cpp
    graphmodel.h
    graphpropertywidget.cpp
    graphpropertywidget.h
    graphwidget.cpp
    graphwidget.h
    mainwindow.cpp
    mainwindow.h
)

