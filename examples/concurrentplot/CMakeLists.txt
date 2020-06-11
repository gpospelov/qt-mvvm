# executable: concurrentplot

add_subdirectory(concurrentplotcore)

add_executable(concurrentplot main.cpp)
target_link_libraries(concurrentplot PRIVATE concurrentplotcore Qt5::Widgets)

target_include_directories(concurrentplot PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
