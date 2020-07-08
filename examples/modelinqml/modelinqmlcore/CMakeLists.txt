# library: flateditorcore
set(library_name modelinqmlcore)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_library(${library_name} STATIC "")
target_link_libraries(${library_name} PUBLIC MVVM::View Qt5::Qml Qt5::Quick)

target_sources(${library_name} PRIVATE
    tablemodel.h
    backend.cpp
    backend.h
    modelinqmlcore.qrc
    particlemodel.cpp
    particlemodel.h
    particleviewmodel.cpp
    particleviewmodel.h
)

target_include_directories(${library_name} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/..)
