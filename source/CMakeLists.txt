# -----------------------------------------------------------------------------
# Entry point for all project libraries
# -----------------------------------------------------------------------------

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

add_subdirectory(libmvvm_model)
add_subdirectory(libmvvm_viewmodel)
add_subdirectory(libmvvm_view)
