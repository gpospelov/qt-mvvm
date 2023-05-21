cmake_minimum_required(VERSION 3.14)
project(plotcolormap_example VERSION 0.0.1 LANGUAGES CXX)

find_package(MVVM REQUIRED)

set(executable_name plotcolormap)
add_subdirectory(plotcolormapcore)
add_executable(${executable_name} main.cpp)

target_link_libraries(${executable_name} plotcolormapcore Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(${executable_name} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
