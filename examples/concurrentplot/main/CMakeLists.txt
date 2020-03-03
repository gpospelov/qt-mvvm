set(executable_name concurrentplot)

add_executable(${executable_name} main.cpp)
target_link_libraries(${executable_name} PRIVATE concurrentplotcore)
