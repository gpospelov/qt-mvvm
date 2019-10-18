set(executable_name plotcolormap)

add_executable(${executable_name} main.cpp)
target_link_libraries(${executable_name} PRIVATE mvvm plotcolormapcore)
