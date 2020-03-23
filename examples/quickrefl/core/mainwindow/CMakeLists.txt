# Static library: quickreflcore.

target_sources(quickreflcore PRIVATE
    mainwindow.cpp
    mainwindow.h
    mainbarwidget.cpp
    mainbarwidget.h
    refldockwindow.cpp
    refldockwindow.h
    dockscontroller.cpp
    dockscontroller.h
    reflwidgets.cpp
    reflwidgets.h
    styleutils.cpp
    styleutils.h
)

target_include_directories(quickreflcore PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
