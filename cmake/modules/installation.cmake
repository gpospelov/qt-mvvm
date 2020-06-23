# -----------------------------------------------------------------------------
# Installation
# Credits to https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right,
# https://gitlab.kitware.com/cmake/community/-/wikis/doc/tutorials/Exporting-and-Importing-Targets
# -----------------------------------------------------------------------------

set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/mvvm)

# exporting targets to a script and installing it
install(EXPORT mvvm-targets FILE MVVMTargets.cmake NAMESPACE MVVM:: DESTINATION ${INSTALL_CONFIGDIR})

# -----------------------------------------------------------------------------
# Exporting
# -----------------------------------------------------------------------------

# Add all targets to the build-tree export set
export(TARGETS mvvm_model mvvm_viewmodel mvvm_view NAMESPACE MVVM:: FILE MVVMTargets.cmake)

# Export the package for use from the build-tree (goes to $HOME/.cmake)
export(PACKAGE MVVM)

# -----------------------------------------------------------------------------
# Creating and installing MVVMConfig.cmake
# -----------------------------------------------------------------------------

include(CMakePackageConfigHelpers)

configure_package_config_file(${CMAKE_SOURCE_DIR}/cmake/scripts/MVVMConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/MVVMConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/MVVMConfig.cmake DESTINATION ${INSTALL_CONFIGDIR})

# -----------------------------------------------------------------------------
# Create and install ConfigVersion.cmake file
# -----------------------------------------------------------------------------

write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/MVVMConfigVersion.cmake VERSION
    ${PROJECT_VERSION} COMPATIBILITY AnyNewerVersion)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/MVVMConfigVersion.cmake DESTINATION ${INSTALL_CONFIGDIR})
