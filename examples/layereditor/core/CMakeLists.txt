set(library_name layereditorcore)

add_library(${library_name} STATIC "")

add_subdirectory(mainwindow)
add_subdirectory(model)
add_subdirectory(viewmodel)

target_link_libraries(${library_name} PUBLIC mvvm_model Qt5::Core Qt5::Gui Qt5::Widgets)

