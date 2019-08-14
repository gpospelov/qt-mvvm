set(executable_name plotgraphs)

add_executable(${executable_name} main.cpp)
target_link_libraries(${executable_name} PRIVATE mvvm plotgraphscore)
