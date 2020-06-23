# -----------------------------------------------------------------------------
# Library: mvvm_model
# -----------------------------------------------------------------------------
set(library_name mvvm_model)

add_library(${library_name} SHARED "")

add_subdirectory(mvvm)

# Add an alias so that library can be used inside the build tree, e.g. when testing
add_library(MVVM::Model ALIAS ${library_name})

generate_export_header(${library_name})

target_link_libraries(${library_name} PUBLIC Qt5::Widgets Threads::Threads)

target_include_directories(${library_name}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}> $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
#    $<INSTALL_INTERFACE:${CMAKE_CURRENT_LIST_DIR}> $<INSTALL_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    )

# to make clang code model in Qt creator happy
target_compile_features(${library_name} PUBLIC cxx_std_17)

if (MVVM_ENABLE_FILESYSTEM)
    add_definitions(-DENABLE_FILESYSTEM)
endif()

# -----------------------------------------------------------------------------
# Installation instructions
# Based on https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/
# -----------------------------------------------------------------------------

#set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/mvvm)

message(INFO "AAA ${CMAKE_INSTALL_LIBDIR} aaa${CMAKE_INSTALL_PREFIX}")
install(TARGETS ${library_name} EXPORT mvvm-targets LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

# This is required so that the exported target has the name MVVM and not mvvm
set_target_properties(${library_name} PROPERTIES EXPORT_NAME Model)

install(DIRECTORY mvvm/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mvvm FILES_MATCHING PATTERN "*.h")

##Export the targets to a script
#install(EXPORT ${library_name}-targets
#    FILE MVVMTargets.cmake NAMESPACE MVVM:: DESTINATION ${INSTALL_CONFIGDIR})

#Create a ConfigVersion.cmake file
#include(CMakePackageConfigHelpers)
#write_basic_package_version_file(
#    ${CMAKE_CURRENT_BINARY_DIR}/MVVMConfigVersion.cmake
#    VERSION ${PROJECT_VERSION}
#    COMPATIBILITY AnyNewerVersion
#)

#configure_package_config_file(${CMAKE_SOURCE_DIR}/cmake/scripts/MVVMConfig.cmake.in
#    ${CMAKE_CURRENT_BINARY_DIR}/MVVMConfig.cmake
#    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
#)

##Install the config, configversion and custom find modules
#install(FILES
#    ${CMAKE_CURRENT_BINARY_DIR}/MVVMConfig.cmake
#    ${CMAKE_CURRENT_BINARY_DIR}/MVVMConfigVersion.cmake
#    DESTINATION ${INSTALL_CONFIGDIR}
#)

###############################################
### Exporting from the build tree
#export(EXPORT ${library_name}-targets FILE ${CMAKE_CURRENT_BINARY_DIR}/FancyLibTargets.cmake NAMESPACE FancyLib::)

##Register package in user's package registry
#export(PACKAGE FancyLib)
