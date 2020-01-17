# Static library: quickreflcore.

target_sources(quickreflcore PRIVATE
    mainwindow.cpp
    mainwindow.h
    refldockwindow.cpp
    refldockwindow.h
    dockscontroller.cpp
    dockscontroller.h
    reflwidgets.cpp
    reflwidgets.h
)

target_include_directories(quickreflcore PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
