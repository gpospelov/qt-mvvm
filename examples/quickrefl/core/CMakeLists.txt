set(library_name quickreflcore)

add_library(${library_name} STATIC "")

add_subdirectory(mainwindow)
add_subdirectory(model)
add_subdirectory(editors/layereditor)
add_subdirectory(editors/materialeditor)
add_subdirectory(editors/sldeditor/models)
add_subdirectory(editors/sldeditor/scene)
add_subdirectory(editors/sldeditor/viewobjects)
add_subdirectory(editors/sldeditor/widgets)
add_subdirectory(editors/quicksimeditor)
add_subdirectory(resources)

target_link_libraries(${library_name} PUBLIC mvvm_viewmodel Qt5::Core Qt5::Gui Qt5::Widgets)

