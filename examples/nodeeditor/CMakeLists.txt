cmake_minimum_required(VERSION 3.14)
project(nodeeditor_example VERSION 0.0.1 LANGUAGES CXX)

find_package(MVVM REQUIRED)

set(executable_name nodeeditor)
add_subdirectory(nodeeditorcore)
add_executable(${executable_name} main.cpp)

target_link_libraries(${executable_name} nodeeditorcore Qt5::Widgets)
target_include_directories(${executable_name} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
