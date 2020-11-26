set(library_name plotgraphscore)

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
    mainwindow.cpp
    mainwindow.h
)
