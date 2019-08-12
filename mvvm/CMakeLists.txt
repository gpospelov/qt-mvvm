set(library_name mvvm)

if(WIN32)
    add_definitions(-DCORE_BUILD_DLL)
endif()

add_library(${library_name} SHARED "")

add_subdirectory(commands)
add_subdirectory(editors)
add_subdirectory(model)
add_subdirectory(public)
add_subdirectory(serialization)
add_subdirectory(standarditems)
add_subdirectory(utils)
add_subdirectory(viewmodel)
add_subdirectory(widgets)

target_link_libraries(${library_name} Qt5::Widgets)

# Manually composing list of dirs with private API for unit testing.
set(private_include_dirs
    ${CMAKE_CURRENT_LIST_DIR}/commands
    ${CMAKE_CURRENT_LIST_DIR}/serialization
    ${CMAKE_CURRENT_LIST_DIR}/editors
    )
set(MVVM_PRIVATE_API ${private_include_dirs} CACHE INTERNAL "")
