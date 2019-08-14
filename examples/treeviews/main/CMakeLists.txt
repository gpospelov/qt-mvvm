set(executable_name treeviews)

add_executable(${executable_name} main.cpp)
target_link_libraries(${executable_name} PUBLIC treeviewscore)
