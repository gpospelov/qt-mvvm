set(library_name layereditorcore)

set(CMAKE_AUTOMOC ON)

add_library(${library_name} STATIC "")

add_subdirectory(widgets)
add_subdirectory(model)
add_subdirectory(viewmodel)

target_link_libraries(${library_name} PRIVATE MVVM::View)

target_include_directories(${library_name} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/..)
