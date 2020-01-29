set(library_name sldeditorcore)

target_sources(${library_name} PRIVATE
    AxisViewWidget.h
    AxisViewWidget.cpp
    AxisObject.h
    AxisObject.cpp
    TicksView.h
    TicksView.cpp
)

target_include_directories(${library_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
