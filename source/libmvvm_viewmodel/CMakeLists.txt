# -----------------------------------------------------------------------------
# Library: mvvm_viewmodel
# -----------------------------------------------------------------------------
set(library_name mvvm_viewmodel)

add_library(${library_name} SHARED "")

add_subdirectory(mvvm)

# Add an alias so that library can be used inside the build tree, e.g. when testing
add_library(MVVM::ViewModel ALIAS ${library_name})

generate_export_header(${library_name})

target_link_libraries(${library_name} PUBLIC mvvm_model Qt5::Widgets)
target_include_directories(${library_name}
    PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}> $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    )

# to make clang code model in Qt creator happy
target_compile_features(${library_name} PUBLIC cxx_std_17)

# -----------------------------------------------------------------------------
# Installation
# -----------------------------------------------------------------------------

install(TARGETS ${library_name} EXPORT mvvm-targets LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

set_target_properties(${library_name} PROPERTIES EXPORT_NAME ViewModel)

install(DIRECTORY mvvm/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mvvm FILES_MATCHING PATTERN "*.h")
