# Installation and exporting

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/mvvm)

#Export the targets to a script
install(EXPORT mvvm-targets FILE MVVMTargets.cmake NAMESPACE MVVM:: DESTINATION ${INSTALL_CONFIGDIR})


# #############################################################################
# Export
# #############################################################################

#export(TARGETS mvvm_model mvvm_viewmodel- NAMESPACE MVVM:: FILE MVVMTargets.cmake)
#export(PACKAGE MVVM)
