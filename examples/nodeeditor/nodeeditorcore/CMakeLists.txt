set(library_name nodeeditorcore)

set(CMAKE_AUTOMOC ON)

add_library(${library_name} STATIC "")
target_link_libraries(${library_name} PRIVATE MVVM::View)

target_sources(${library_name} PRIVATE
    connectableitem.cpp
    connectableitem.h
    connectableitemcontroller.cpp
    connectableitemcontroller.h
    connectableview.cpp
    connectableview.h
    graphicsscene.cpp
    graphicsscene.h
    graphicsscenecontroller.cpp
    graphicsscenecontroller.h
    graphicsview.cpp
    graphicsview.h
    mainwindow.cpp
    mainwindow.h
    modeleditorwidget.cpp
    modeleditorwidget.h
    nodeconnection.cpp
    nodeconnection.h
    nodecontroller.cpp
    nodecontroller.h
    nodeport.cpp
    nodeport.h
    pieceslist.cpp
    pieceslist.h
    portinfo.h
    propertywidget.cpp
    propertywidget.h
    sampleitems.cpp
    sampleitems.h
    samplemodel.cpp
    samplemodel.h
    sceneutils.cpp
    sceneutils.h
)

