cmake_minimum_required(VERSION 3.14)
project(helloworld_example VERSION 0.0.1 LANGUAGES CXX)

find_package(MVVM REQUIRED)

set(executable_name helloworld)
add_executable(${executable_name} main.cpp)

target_link_libraries(${executable_name} PRIVATE Qt5::Widgets MVVM::View)
