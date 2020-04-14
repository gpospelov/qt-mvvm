# Static library: quickreflcore.

target_sources(quickreflcore PRIVATE
    dockscontroller.cpp
    dockscontroller.h
    importwindow.cpp
    importwindow.h
    mainbarwidget.cpp
    mainbarwidget.h
    mainwindow.cpp
    mainwindow.h
    refldockwindow.cpp
    refldockwindow.h
    reflwidgets.cpp
    reflwidgets.h
    styleutils.cpp
    styleutils.h
)

target_include_directories(quickreflcore PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
