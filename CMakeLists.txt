cmake_minimum_required(VERSION 3.15)

project(qt-mvvm VERSION 0.2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

option(MVVM_BUMP_VERSION "Propagate version number" OFF)
option(MVVM_USE_QT6 "Compile with Qt6" ON)
option(MVVM_DISCOVER_TESTS "Auto discover tests and add to ctest, otherwise will run at compile time" ON)
option(MVVM_ENABLE_FILESYSTEM "Enable <filesystem> (requires modern compiler), otherwise rely on Qt" ON)
option(MVVM_BUILD_EXAMPLES "Build user examples" ON)
option(MVVM_SETUP_CLANGFORMAT "Setups target to beautify the code with 'make clangformat'" OFF)
option(MVVM_ENABLE_EXTRA_COMPILER_WARNINGS "Enable additional compiler warnings (e.g. for code quality reviewing)" OFF)

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

add_compile_definitions(GTEST_LINKED_AS_SHARED_LIBRARY=0)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/modules)
include(configuration)

message(STATUS "Building for: ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_PROCESSOR}")

if(MSVC)

    if(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
        message(STATUS "MSVC: C VERSION=${CMAKE_C_COMPILER_VERSION} ${CMAKE_C_COMPILER_ARCHITECTURE_ID}")
        message(STATUS "MSVC: C COMPILER=${CMAKE_C_COMPILER}")
        message(STATUS "MSVC: CMAKE_C_FLAGS=${CMAKE_C_FLAGS}")
        message(STATUS "MSVC: CMAKE_C_FLAGS_DEBUG=${CMAKE_C_FLAGS_DEBUG}")
        message(STATUS "MSVC: CMAKE_C_FLAGS_RELEASE=${CMAKE_C_FLAGS_RELEASE}")
        message(STATUS "MSVC: CMAKE_C_FLAGS_MINSIZEREL=${CMAKE_C_FLAGS_MINSIZEREL}")
        message(STATUS "MSVC: CMAKE_C_FLAGS_RELWITHDEBINFO=${CMAKE_C_FLAGS_RELWITHDEBINFO}")
    endif()
    
    if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        message(STATUS "MSVC: CXX VERSION=${CMAKE_CXX_COMPILER_VERSION} ARCHITECTURE=${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}")
        message(STATUS "MSVC: CXX COMPILER=${CMAKE_CXX_COMPILER}")
        message(STATUS "MSVC: CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}")
        message(STATUS "MSVC: CMAKE_CXX_FLAGS_DEBUG=${CMAKE_CXX_FLAGS_DEBUG}")
        message(STATUS "MSVC: CMAKE_CXX_FLAGS_RELEASE=${CMAKE_CXX_FLAGS_RELEASE}")
        message(STATUS "MSVC: CMAKE_CXX_FLAGS_MINSIZEREL=${CMAKE_CXX_FLAGS_MINSIZEREL}")
        message(STATUS "MSVC: CMAKE_CXX_FLAGS_RELWITHDEBINFO=${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
    endif()

    # https://github.com/cpp-best-practices/cmake_template/blob/main/cmake/CompilerWarnings.cmake

    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded" CACHE STRING "" FORCE)

    # Set /MP (Build with multiple processes):
    # https://learn.microsoft.com/en-us/cpp/build/reference/mp-build-with-multiple-processes
    add_compile_options(/MP)

    # Warning level:
    # https://learn.microsoft.com/en-us/cpp/build/reference/compiler-option-warning-level

    # Remove any previously set MSVC warning level flags:
    string(REGEX REPLACE "\/W[A-Za-z0-9:]*" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    string(REGEX REPLACE "\/W[A-Za-z0-9:]*" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

    if(MVVM_ENABLE_EXTRA_COMPILER_WARNINGS)
        add_compile_options(/Wall)
    else()
        add_compile_options(/W3)
    endif()
    
else()

    # https://gcovr.com/en/stable/cookbook.html#oos-cmake
    # https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html
    
    # These flags are used if cmake is called with -DCMAKE_BUILD_TYPE=PROFILE:
    set(CMAKE_C_FLAGS_PROFILE "--coverage")
    set(CMAKE_CXX_FLAGS_PROFILE "--coverage")
    
    # Warning level:
    # https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html

    # Remove any previously set MSVC warning level flags:
    string(REGEX REPLACE "\-W[A-Za-z0-9=\-]*" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    string(REGEX REPLACE "\-W[A-Za-z0-9=\-]*" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

    if(MVVM_ENABLE_EXTRA_COMPILER_WARNINGS)
        add_compile_options(
            -Wall
            -Wextra
            -Wpedantic
            -Wcast-align
            -Wconversion
            -Wdouble-promotion
            -Wduplicated-branches
            -Wduplicated-cond
            -Wfloat-equal
            -Wformat=2
            -Wlogical-op
            -Wmissing-declarations
            -Wmissing-include-dirs
            -Wnon-virtual-dtor
            -Wnull-dereference
            -Wold-style-cast
            -Wpointer-arith
            -Wredundant-decls
            -Wshadow
            -Wsign-conversion
            -Wstrict-aliasing=2
            -Wstrict-overflow=5
            -Wswitch-enum
            -Wunreachable-code
            -Wunused
            -Wuseless-cast
        )
    else()
        add_compile_options(
            -Wall
            -Wextra
            -Wpedantic
        )
    endif()

endif()

get_directory_property(compile_options COMPILE_OPTIONS)
message(STATUS "COMPILE_OPTIONS=${compile_options}")

add_subdirectory(thirdparty)
add_subdirectory(source)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif(BUILD_TESTING)

include(installation)
add_subdirectory(examples)

# Defines 'clangformat' targets. See CodeTools.cmake for details.
project_codetools_setup()
