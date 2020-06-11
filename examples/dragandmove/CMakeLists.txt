# executable: dragandmove

add_subdirectory(dragandmovecore)

add_executable(dragandmove main.cpp)
target_link_libraries(dragandmove PRIVATE dragandmovecore Qt5::Widgets)

target_include_directories(dragandmove PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
