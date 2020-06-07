# library: libsaveloadprojectcore

set(library_name saveloadprojectcore)

add_library(${library_name} STATIC "")
target_link_libraries(${library_name} PUBLIC mvvm_viewmodel Qt5::Core Qt5::Gui Qt5::Widgets)

target_sources(${library_name} PRIVATE
    mainwindow.cpp
    mainwindow.h
    actionmanager.cpp
    actionmanager.h
)

target_include_directories(${library_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
