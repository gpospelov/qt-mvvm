# library: celleditorscore
set(library_name layereditorcore)

set(CMAKE_AUTOMOC ON)

add_library(${library_name} STATIC "")
target_link_libraries(${library_name} PRIVATE MVVM::View)

target_sources(${library_name} PRIVATE
    applicationmodels.cpp
    applicationmodels.h
    customeditorfactory.cpp
    customeditorfactory.h
    customlayerrowstrategy.h
    multilayertreeview.cpp
    multilayertreeview.h
    mainwindow.cpp
    mainwindow.h
    materialmodel.cpp
    materialmodel.h
    materialpropertycontroller.cpp
    materialpropertycontroller.h
    materialtablewidget.cpp
    materialtablewidget.h
    samplemodel.cpp
    samplemodel.h
    samplewidget.cpp
    samplewidget.h
)

target_include_directories(${library_name} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/..)
