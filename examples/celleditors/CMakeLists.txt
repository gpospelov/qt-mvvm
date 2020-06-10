# executable: celleditors

add_subdirectory(celleditorscore)

add_executable(celleditors main.cpp)
target_link_libraries(celleditors PRIVATE celleditorscore Qt5::Widgets)

target_include_directories(celleditors PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
