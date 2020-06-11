# executable: graphicsproxy

add_subdirectory(graphicsproxycore)

add_executable(graphicsproxy main.cpp)
target_link_libraries(graphicsproxy PRIVATE graphicsproxycore Qt5::Widgets)

target_include_directories(graphicsproxy PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
