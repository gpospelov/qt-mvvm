cmake_minimum_required(VERSION 3.14)
project(qt-mvvm VERSION 0.2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

option(MVVM_BUMP_VERSION "Propagate version number" OFF)
option(MVVM_DISCOVER_TESTS "Auto discover tests and add to ctest, otherwise will run at compile time" ON)
option(MVVM_ENABLE_FILESYSTEM "Enable <filesystem> (requires modern compiler), otherwise rely on Qt" ON)
option(MVVM_BUILD_EXAMPLES "Build user examples" ON)
option(MVVM_GENERATE_COVERAGE "Generate test coverage information with 'make coverage'" ON)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/modules)
include(configuration)

add_subdirectory(source)
add_subdirectory(thirdparty)
add_subdirectory(tests)

include(installation)
add_subdirectory(examples)

#setup_target_for_coverage_lcov(
#          NAME coverage
#          EXECUTABLE ctest -j ${n_cores}
#          DEPENDENCIES testmodel testviewmodel testview testintegration
#          )

setup_target_for_coverage_lcov(NAME coverage
    EXECUTABLE ctest -R Model.* ViewModel.* -j ${n_cores}
    DEPENDENCIES testmodel testviewmodel testview testintegration
    EXCLUDE "${PROJECT_SOURCE_DIR}/thirdparty/*" "${PROJECT_SOURCE_DIR}/tests/*" "${PROJECT_SOURCE_DIR}/examples/*" "**CompilerId*" "/usr/*"  "*build*"
    )

#setup_target_for_coverage_lcov(NAME coverage
#    EXECUTABLE testmodel
#    DEPENDENCIES testmodel
#    EXCLUDE "${PROJECT_SOURCE_DIR}/thirdparty/*" "${PROJECT_SOURCE_DIR}/tests/*" "${PROJECT_SOURCE_DIR}/examples/*" "**CompilerId*" "/usr/*" "*/build*/*"
#    )



# Defines new 'clangformat' target. See CodeTools.cmake for details.
# project_clangformat_setup()
