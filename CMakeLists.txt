cmake_minimum_required(VERSION 3.10)
project(qt-mvvm)

option(MVVM_TESTS_AUTOEXEC "Execute tests automatically at the end of the build" ON)
option(MVVM_TESTS_AUTODISCOVERY "Auto discover tests and add to ctest" ON)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

include(CTest)
include(configuration)

add_subdirectory(mvvm)
add_subdirectory(app)
add_subdirectory(thirdparty/gtest)
add_subdirectory(tests)



 
