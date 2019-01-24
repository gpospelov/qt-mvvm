set(library_name mvvm)

set(include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/model
    ${CMAKE_CURRENT_SOURCE_DIR}/viewmodel
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/serialization)

set(source_files)
set(include_files)

foreach(dir ${include_dirs})
    file(GLOB source ${dir}/*.cpp)
    file(GLOB include ${dir}/*.h)
    list(APPEND source_files ${source})
    list(APPEND include_files ${include})
endforeach()

if(WIN32)
    add_definitions(-DCORE_BUILD_DLL)
endif()

add_library(${library_name} SHARED ${source_files} ${include_files})

target_include_directories(${library_name}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/model>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/viewmodel>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/utils>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/serialization>
)

target_link_libraries(${library_name} Qt5::Widgets)
