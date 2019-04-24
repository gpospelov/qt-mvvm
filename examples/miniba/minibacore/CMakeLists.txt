set(library_name minibacore)

# --- source and include files ---
set(include_dirs ${CMAKE_CURRENT_SOURCE_DIR})

set(source_files)
set(include_files)

foreach(dir ${include_dirs})
    file(GLOB source ${dir}/*.cpp)
    file(GLOB include ${dir}/*.h)
    list(APPEND source_files ${source})
    list(APPEND include_files ${include})
endforeach()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

if(WIN32)
    add_definitions(-DCORE_BUILD_DLL)
endif()

add_library(${library_name} SHARED ${source_files} ${include_files})

target_include_directories(${library_name} PUBLIC ${include_dirs})

target_link_libraries(${library_name} mvvm Qt5::Core Qt5::Gui Qt5::Widgets)

