cmake_minimum_required(VERSION 3.14)
project(qt-mvvm VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

option(MVVM_BUMP_VERSION "Propagate version number" ON)
option(MVVM_GTEST_DISCOVER_TESTS "Auto discover tests and add to ctest, otherwise will run at compile time" ON)
option(MVVM_ENABLE_FILESYSTEM "Enable <filesystem> (requires modern compiler), otherwise rely on Qt" ON)
option(MVVM_BUILD_EXAMPLES "Build user examples" ON)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

include(CTest)
include(configuration)
include(CodeTools)
include(GenerateExportHeader)

add_subdirectory(source)
add_subdirectory(examples)
add_subdirectory(thirdparty)
add_subdirectory(tests)

# Defines new 'clangformat' target. See CodeTools.cmake for details.
# project_clangformat_setup()
