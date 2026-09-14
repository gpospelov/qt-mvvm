############################################################################
# CMakeLists.txt file for building qcustomplot static library
############################################################################

cmake_minimum_required(VERSION 3.15)

project(qcustomplot LANGUAGES CXX)
set(library_name qcustomplot)

if(NOT DEFINED CMAKE_CXX_STANDARD OR CMAKE_CXX_STANDARD STREQUAL "")
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

# There are many code quality issues in the qcustomplot project, thus the build output
# of any project including it would get flooded by the respective warnings, therefore
# the warnings are disabled here by default.
option(QCUSTOMPLOT_ENABLE_COMPILER_WARNINGS "Enable compiler warnings for qcustomplot." OFF)

if((CMAKE_C_COMPILER_ID STREQUAL "MSVC") OR (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC"))

  # https://learn.microsoft.com/en-us/cpp/build/reference/compiler-option-warning-level

  # Remove any previously set MSVC warning level flags:
  get_directory_property(compile_options COMPILE_OPTIONS)
  string(REGEX REPLACE "\/W[A-Za-z0-9:]*" "" compile_options "${compile_options}")
  set_property(DIRECTORY PROPERTY COMPILE_OPTIONS "${compile_options}")

  if (QCUSTOMPLOT_ENABLE_COMPILER_WARNINGS)
    message(STATUS "[QCUSTOMPLOT] Enabled compiler warnings.")
    add_compile_options(/Wall)
  else()
    message(STATUS "[QCUSTOMPLOT] Disabled compiler warnings.")
    add_compile_options(/W0)
  endif()
 
else()

  # https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html

  # Remove any previously set gcc warning level flags:
  get_directory_property(compile_options COMPILE_OPTIONS)
  string(REGEX REPLACE "\-W[A-Za-z0-9=\-]*" "" compile_options "${compile_options}")
  set_property(DIRECTORY PROPERTY COMPILE_OPTIONS "${compile_options}")

  if (QCUSTOMPLOT_ENABLE_COMPILER_WARNINGS)
    message(STATUS "[QCUSTOMPLOT] Enabled compiler warnings.")
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wsign-conversion
        -Wshadow
        -Wdouble-promotion
        -Wformat=2
        -Wnull-dereference
        -Wduplicated-cond
        -Wduplicated-branches
        -Wlogical-op
        -Wuseless-cast
        -Wold-style-cast
        -Wnon-virtual-dtor
        -Wcast-align
        -Wmissing-include-dirs
        -Wswitch-enum
        -Wunreachable-code
        -Wfloat-equal
        -Wstrict-overflow=5
        -Wstrict-aliasing=2
        -Wpointer-arith
        -Wredundant-decls
        -Wmissing-declarations
    )
  else()
    message(STATUS "[QCUSTOMPLOT] Disabled compiler warnings.")
    add_compile_options(-w)
  endif()
 
endif()

get_directory_property(compile_options COMPILE_OPTIONS)
message(STATUS "[QCUSTOMPLOT] COMPILE_OPTIONS=${compile_options}")

message(STATUS "[QCUSTOMPLOT] C VERSION=${CMAKE_C_COMPILER_VERSION} ${CMAKE_C_COMPILER_ARCHITECTURE_ID}")
message(STATUS "[QCUSTOMPLOT] C COMPILER=${CMAKE_C_COMPILER}")
message(STATUS "[QCUSTOMPLOT] CMAKE_C_FLAGS=${CMAKE_C_FLAGS}")
message(STATUS "[QCUSTOMPLOT] CMAKE_C_FLAGS_DEBUG=${CMAKE_C_FLAGS_DEBUG}")
message(STATUS "[QCUSTOMPLOT] CMAKE_C_FLAGS_RELEASE=${CMAKE_C_FLAGS_RELEASE}")
message(STATUS "[QCUSTOMPLOT] CMAKE_C_FLAGS_MINSIZEREL=${CMAKE_C_FLAGS_MINSIZEREL}")
message(STATUS "[QCUSTOMPLOT] CMAKE_C_FLAGS_RELWITHDEBINFO=${CMAKE_C_FLAGS_RELWITHDEBINFO}")
message(STATUS "[QCUSTOMPLOT] CXX VERSION=${CMAKE_CXX_COMPILER_VERSION} ARCHITECTURE=${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}")
message(STATUS "[QCUSTOMPLOT] CXX COMPILER=${CMAKE_CXX_COMPILER}")
message(STATUS "[QCUSTOMPLOT] CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}")
message(STATUS "[QCUSTOMPLOT] CMAKE_CXX_FLAGS_DEBUG=${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "[QCUSTOMPLOT] CMAKE_CXX_FLAGS_RELEASE=${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "[QCUSTOMPLOT] CMAKE_CXX_FLAGS_MINSIZEREL=${CMAKE_CXX_FLAGS_MINSIZEREL}")
message(STATUS "[QCUSTOMPLOT] CMAKE_CXX_FLAGS_RELWITHDEBINFO=${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Core Gui PrintSupport Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core Gui PrintSupport Test)

get_target_property(QtWidgets_location Qt${QT_VERSION_MAJOR}::Core LOCATION_Release)

message(STATUS "[QCUSTOMPLOT] Qt${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH} found")
message(STATUS "[QCUSTOMPLOT]  Includes: ${Qt${QT_VERSION_MAJOR}Widgets_INCLUDE_DIRS}")
message(STATUS "[QCUSTOMPLOT]  Core library: ${QtWidgets_location}")

set(CMAKE_AUTOMOC ON)
add_library(${library_name} STATIC qcustomplot.h qcustomplot.cpp)
set_property(TARGET ${library_name} PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(${library_name} PUBLIC Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::PrintSupport)
target_include_directories(${library_name} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_LIBDIR}>
)

install(TARGETS ${library_name} DESTINATION ${CMAKE_INSTALL_LIBDIR} EXPORT ${library_name}-targets)
install(EXPORT ${library_name}-targets DESTINATION ${CMAKE_INSTALL_LIBDIR}/${library_name})
