add_executable(defaultqt main.cpp mainwindow.cpp centralwidget.cpp)
target_link_libraries(defaultqt PUBLIC Qt5::Core Qt5::Gui Qt5::Widgets)
