# library: celleditorscore
set(library_name graphicsproxycore)

set(CMAKE_AUTOMOC ON)

add_library(${library_name} STATIC "")
target_link_libraries(${library_name} PRIVATE MVVM::View)

target_sources(${library_name} PRIVATE
    axesrectangleview.cpp
    axesrectangleview.h
    graphicsscene.cpp
    graphicsscene.h
    graphicsview.cpp
    graphicsview.h
    mainwindow.cpp
    mainwindow.h
    regionofinterestcontroller.cpp
    regionofinterestcontroller.h
    regionofinterestitem.cpp
    regionofinterestitem.h
    regionofinterestview.cpp
    regionofinterestview.h
    scenemodel.cpp
    scenemodel.h
    scenepropertywidget.cpp
    scenepropertywidget.h
    scenewidget.cpp
    scenewidget.h
    sizehandleelement.cpp
    sizehandleelement.h
)
