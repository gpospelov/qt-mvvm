# executable: flateditor

add_subdirectory(flateditorcore)

add_executable(flateditor main.cpp)
target_link_libraries(flateditor PRIVATE flateditorcore Qt5::Widgets)

target_include_directories(flateditor PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
