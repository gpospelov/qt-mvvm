set(executable_name dragandmove)

add_executable(${executable_name} main.cpp)
target_link_libraries(${executable_name} PRIVATE dragandmovecore)
