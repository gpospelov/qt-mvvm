set(executable_name collidingmice)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(${executable_name} main.cpp)
target_link_libraries(${executable_name} PRIVATE Qt5::Widgets mvvm_view)

add_subdirectory(collidingmicecore)
