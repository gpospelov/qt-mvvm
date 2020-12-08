set(library_name saveloadprojectcore)

set(CMAKE_AUTOMOC ON)

add_library(${library_name} STATIC "")
target_link_libraries(${library_name} PRIVATE MVVM::View)

target_sources(${library_name} PRIVATE
    actionmanager.cpp
    actionmanager.h
    containereditorwidget.cpp
    containereditorwidget.h
    mainwindow.cpp
    mainwindow.h
    projecthandler.cpp
    projecthandler.h
    projectpanewidget.cpp
    projectpanewidget.h
    recentprojectsettings.cpp
    recentprojectsettings.h
    recentprojectwidget.cpp
    recentprojectwidget.h
    samplemodel.cpp
    samplemodel.h
    userinteractor.cpp
    userinteractor.h
)

target_include_directories(${library_name} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
