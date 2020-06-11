set(executable_name layereditor)

add_subdirectory(layereditor)

add_executable(${executable_name} main.cpp)
target_link_libraries(${executable_name} PRIVATE layereditorcore Qt5::Widgets)

target_include_directories(${executable_name} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
