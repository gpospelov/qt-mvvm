set(library_name layereditorcore)

target_sources(${library_name} PRIVATE
    LayerTableWidget.cpp
    LayerTableWidget.h
    mainwindow.cpp
    mainwindow.h
    MaterialTableWidget.cpp
    MaterialTableWidget.h
    SampleWidget.cpp
    SampleWidget.h
)

target_include_directories(${library_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
