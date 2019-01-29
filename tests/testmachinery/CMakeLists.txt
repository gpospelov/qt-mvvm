set(library_name testmachinery)

set(include_dirs ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB source_files "*.cpp")
file(GLOB include_files "*.h")

find_package(Qt5Core REQUIRED)
find_package(Qt5Test REQUIRED)

include_directories(${BUILD_INC_DIR})

add_library(${library_name} STATIC ${source_files} ${include_files})
target_link_libraries(${library_name} gtest gmock Qt5::Core Qt5::Test mvvm)
target_include_directories(${library_name} PUBLIC $<BUILD_INTERFACE:${include_dirs}>)
