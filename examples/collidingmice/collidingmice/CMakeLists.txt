# Executable: collidingmice

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(collidingmice main.cpp mouse.h mouse.cpp mice.qrc)
target_link_libraries(collidingmice PUBLIC mvvm_viewmodel Qt5::Core Qt5::Gui Qt5::Widgets)
