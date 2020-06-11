set(executable plotcolormap)

add_subdirectory(plotcolormapcore)

add_executable(${executable} main.cpp)
target_link_libraries(${executable} PRIVATE plotcolormapcore Qt5::Widgets)

target_include_directories(${executable} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
