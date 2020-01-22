set(executable_name sldeditor)

add_executable(${executable_name} main.cpp)
target_link_libraries(${executable_name} PRIVATE sldeditorcore)
