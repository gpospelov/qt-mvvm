set(executable_name layereditor)

add_executable(${executable_name} main.cpp)
target_link_libraries(${executable_name} PRIVATE layereditorcore)
