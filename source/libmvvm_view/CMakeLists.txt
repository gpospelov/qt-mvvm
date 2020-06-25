# -----------------------------------------------------------------------------
# Library: mvvm_view
# -----------------------------------------------------------------------------

set(library_name mvvm_view)

add_library(${library_name} SHARED "")
add_subdirectory(mvvm)
add_library(MVVM::View ALIAS ${library_name}) # alias for build-tree usage

# -- Generate header for export --

set(export_filename ${MVVM_AUTOGEN_DIR}/mvvm/view_export.h)
generate_export_header(${library_name} EXPORT_FILE_NAME ${export_filename})

# -- Dependencies --

target_link_libraries(${library_name} PUBLIC mvvm_viewmodel Qt5::Widgets PRIVATE qcustomplot)
target_include_directories(${library_name}
    PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}> $<BUILD_INTERFACE:${MVVM_AUTOGEN_DIR}>
    )

# -- Definitions --

target_compile_features(${library_name} PUBLIC cxx_std_17) # clang code model in Qt creator

# -- Installation --

install(TARGETS ${library_name} EXPORT mvvm-targets LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
set_target_properties(${library_name} PROPERTIES EXPORT_NAME View SOVERSION ${MVVM_SOVERSION} VERSION ${MVVM_BUILDVERSION})
install(DIRECTORY mvvm/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mvvm FILES_MATCHING PATTERN "*.h")
install(FILES ${export_filename} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mvvm)
