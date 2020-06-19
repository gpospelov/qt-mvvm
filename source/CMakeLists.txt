# -----------------------------------------------------------------------------
# Entry point for all project libraries
# -----------------------------------------------------------------------------

if(WIN32)
    add_definitions(-DCORE_BUILD_DLL)
endif()

add_subdirectory(libmvvm_model)
add_subdirectory(libmvvm_viewmodel)
add_subdirectory(libmvvm_view)
