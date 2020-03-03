set(library_name concurrentplotcore)

file(GLOB source_files ${CMAKE_CURRENT_LIST_DIR}/*.cpp)
file(GLOB include_files ${CMAKE_CURRENT_LIST_DIR}/*.h)

add_library(${library_name} STATIC ${source_files} ${include_files})

target_link_libraries(${library_name} PUBLIC mvvm_viewmodel Qt5::Core Qt5::Gui Qt5::Widgets)
target_include_directories(${library_name} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
