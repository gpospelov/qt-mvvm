# Library: flateditorcore

add_library(flateditorcore STATIC)

target_sources(flateditorcore PRIVATE
    demowidget.cpp
    demowidget.h
    items.cpp
    items.h
    mainwindow.cpp
    mainwindow.h
    samplemodel.cpp
    samplemodel.h
)

target_link_libraries(flateditorcore PUBLIC mvvm_viewmodel Qt5::Core Qt5::Gui Qt5::Widgets)
target_include_directories(flateditorcore PUBLIC ${CMAKE_CURRENT_LIST_DIR})
