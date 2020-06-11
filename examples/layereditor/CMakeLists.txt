set(executable layereditor)

add_subdirectory(layereditor)

add_executable(${executable} main.cpp)
target_link_libraries(${executable} PRIVATE layereditorcore Qt5::Widgets)

target_include_directories(${executable} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
