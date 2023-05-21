cmake_minimum_required(VERSION 3.14)
project(modelinqml_example VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(MVVM REQUIRED)

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core Test Quick Qml REQUIRED)

set(executable_name modelinqml)
add_subdirectory(modelinqmlcore)
add_executable(${executable_name} main.cpp ${CMAKE_CURRENT_LIST_DIR}/qml/app.qrc)

target_link_libraries(${executable_name} modelinqmlcore Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Qml)
target_include_directories(${executable_name} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
