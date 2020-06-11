set(executable_name flateditor)

add_subdirectory(flateditorcore)

add_executable(${executable_name} main.cpp)
target_link_libraries(${executable_name} PRIVATE flateditorcore Qt5::Widgets)

target_include_directories(${executable_name} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
