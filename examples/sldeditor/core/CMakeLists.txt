set(library_name sldeditorcore)

add_library(${library_name} STATIC "")

add_subdirectory(widgets)
add_subdirectory(models)

target_link_libraries(${library_name} PUBLIC mvvm_viewmodel Qt5::Core Qt5::Gui Qt5::Widgets)

