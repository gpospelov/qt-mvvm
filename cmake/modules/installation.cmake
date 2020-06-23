# -----------------------------------------------------------------------------
# Installation
# Credits to https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/
# Credits to https://gitlab.kitware.com/cmake/community/-/wikis/doc/tutorials/Exporting-and-Importing-Targets
# -----------------------------------------------------------------------------

set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/mvvm)

# exporting targets to a script
install(EXPORT mvvm-targets FILE MVVMTargets.cmake NAMESPACE MVVM:: DESTINATION ${INSTALL_CONFIGDIR})

# -----------------------------------------------------------------------------
# Exporting
# -----------------------------------------------------------------------------

# export into build tree
export(TARGETS mvvm_model mvvm_viewmodel mvvm_view NAMESPACE MVVM:: FILE MVVMTargets.cmake)

# export into $HOME/.cmake
export(PACKAGE MVVM)
