# executable: collidingmice

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(collidingmice main.cpp)
target_link_libraries(collidingmice PRIVATE Qt5::Widgets mvvm_viewmodel)

add_subdirectory(collidingmicecore)
