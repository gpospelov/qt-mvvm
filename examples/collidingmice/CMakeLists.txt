cmake_minimum_required(VERSION 3.14)
project(collidingmice_example VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(MVVM REQUIRED)

set(executable_name collidingmice)
add_executable(${executable_name} main.cpp)
add_subdirectory(collidingmicecore)

target_link_libraries(${executable_name} PRIVATE Qt5::Widgets MVVM::View)
target_include_directories(${executable_name} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
