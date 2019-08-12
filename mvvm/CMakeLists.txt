set(library_name mvvm)

if(WIN32)
    add_definitions(-DCORE_BUILD_DLL)
endif()

add_library(${library_name} SHARED "")

add_subdirectory(commands)
add_subdirectory(editors)
add_subdirectory(model)
add_subdirectory(serialization)
add_subdirectory(standarditems)
add_subdirectory(utils)
add_subdirectory(viewmodel)
add_subdirectory(widgets)

target_link_libraries(${library_name} Qt5::Widgets)
