set(executable_name plotgraphs)

add_subdirectory(plotgraphscore)

add_executable(${executable_name} main.cpp)
target_link_libraries(${executable_name} PRIVATE plotgraphscore Qt5::Widgets)

target_include_directories(${executable_name} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
