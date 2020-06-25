# -----------------------------------------------------------------------------
# Library: mvvm_viewmodel
# -----------------------------------------------------------------------------
set(library_name mvvm_viewmodel)

add_library(${library_name} SHARED "")
add_subdirectory(mvvm)
add_library(MVVM::ViewModel ALIAS ${library_name}) # alias for build-tree usage

# -- Generate header for export --

set(export_filename ${MVVM_AUTOGEN_DIR}/mvvm/viewmodel_export.h)
generate_export_header(${library_name} EXPORT_FILE_NAME ${export_filename})

# -- Dependencies --

target_link_libraries(${library_name} PUBLIC mvvm_model Qt5::Widgets)
target_include_directories(${library_name}
    PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}> $<BUILD_INTERFACE:${MVVM_AUTOGEN_DIR}>
    )

# -- Definitions --

target_compile_features(${library_name} PUBLIC cxx_std_17)

# -- Installation --

install(TARGETS ${library_name} EXPORT mvvm-targets LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
set_target_properties(${library_name} PROPERTIES EXPORT_NAME ViewModel SOVERSION ${MVVM_SOVERSION} VERSION ${MVVM_BUILDVERSION})
install(DIRECTORY mvvm/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mvvm FILES_MATCHING PATTERN "*.h")
install(FILES ${export_filename} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mvvm)
