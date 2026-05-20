cmake_minimum_required(VERSION 3.14)
project(qt-mvvm VERSION 0.2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

option(MVVM_BUMP_VERSION "Propagate version number" OFF)
option(MVVM_USE_QT6 "Compile with Qt6" ON)
option(MVVM_DISCOVER_TESTS "Auto discover tests and add to ctest, otherwise will run at compile time" ON)
option(MVVM_ENABLE_FILESYSTEM "Enable <filesystem> (requires modern compiler), otherwise rely on Qt" ON)
option(MVVM_BUILD_EXAMPLES "Build user examples" ON)
option(MVVM_SETUP_CLANGFORMAT "Setups target to beautify the code with 'make clangformat'" OFF)
option(MVVM_SETUP_CODECOVERAGE "Setups target to generate coverage information with 'make coverage'" OFF)

find_program(NINJA_PROGRAM ninja)
if(NINJA_PROGRAM)
    message(STATUS "Found ninja: ${NINJA_PROGRAM}.")
endif()

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    message(STATUS "Found ccache: ${CCACHE_PROGRAM}.")
endif()

if(CMAKE_C_COMPILER_LAUNCHER)
    message(STATUS "CMAKE_C_COMPILER_LAUNCHER set: ${CMAKE_C_COMPILER_LAUNCHER}.")
endif()

if(CMAKE_CXX_COMPILER_LAUNCHER)
    message(STATUS "CMAKE_CXX_COMPILER_LAUNCHER set: ${CMAKE_CXX_COMPILER_LAUNCHER}.")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/modules)
include(configuration)

add_subdirectory(source)
add_subdirectory(thirdparty)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif(BUILD_TESTING)

include(installation)
add_subdirectory(examples)

# Defines 'codecoverage', 'clangformat' targets. See CodeTools.cmake for details.
project_codetools_setup()
