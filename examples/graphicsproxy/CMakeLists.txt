cmake_minimum_required(VERSION 3.14)
project(graphicsproxy_example VERSION 0.0.1 LANGUAGES CXX)

find_package(MVVM REQUIRED)

set(executable_name graphicsproxy)
add_subdirectory(graphicsproxycore)
add_executable(${executable_name} main.cpp)

target_link_libraries(${executable_name} graphicsproxycore Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(${executable_name} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
