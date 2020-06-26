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
export(TARGETS mvvm_model mvvm_viewmodel mvvm_view NAMESPACE MVVM:: FILE "${PROJECT_BINARY_DIR}/MVVMTargets.cmake")

# Export the package for use from the build-tree (goes to $HOME/.cmake)
set(CMAKE_EXPORT_PACKAGE_REGISTRY ON)
export(PACKAGE MVVM)

# -----------------------------------------------------------------------------
# Creating and installing MVVMConfig.cmake
# -----------------------------------------------------------------------------

include(CMakePackageConfigHelpers)

# to use in the build tree
configure_package_config_file(${MVVM_PROJECT_DIR}/cmake/scripts/MVVMConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/MVVMConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

# to use in install tree
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/MVVMConfig.cmake DESTINATION ${INSTALL_CONFIGDIR})

# -----------------------------------------------------------------------------
# Create and install ConfigVersion.cmake file
# -----------------------------------------------------------------------------

write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/MVVMConfigVersion.cmake VERSION
    ${PROJECT_VERSION} COMPATIBILITY AnyNewerVersion)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/MVVMConfigVersion.cmake DESTINATION ${INSTALL_CONFIGDIR})


# -----------------------------------------------------------------------------
# TarBall
# -----------------------------------------------------------------------------

# Generating the source package
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "qt-mvvm-${MVVM_BUILDVERSION}")

set(CPACK_SOURCE_IGNORE_FILES
    ${CPACK_SOURCE_IGNORE_FILES} # first take the default parameters
    "/\\\\.git/"
    "/\\\\.gitattributes$"
    "/\\\\.github/"
    "/\\\\.gitmodules"
    "/\\\\.gitignore$"
    "/\\\\.tokeignore$"
    "/\\\\.clang-format"
    "/\\\\.clang-tidy"
    "qt-mvvm.code*"
    "CMakeLists.txt.user"
    "build/"
    "/\\\\.ccache"
)

include(CPack)
