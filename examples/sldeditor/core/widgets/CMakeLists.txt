set(library_name sldeditorcore)

target_sources(${library_name} PRIVATE
    MainWindow.cpp
    MainWindow.h
    ViewWidget.cpp
    ViewWidget.h
    Handle.h
    Handle.cpp
    Segment.h
    Segment.cpp
)

target_include_directories(${library_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
