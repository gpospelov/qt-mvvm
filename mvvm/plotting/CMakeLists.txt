set(library_name mvvm)

target_sources(${library_name} PRIVATE
    colormapcanvas.h
    colormapcanvas.cpp
    colormapplotcontroller.h
    colormapplotcontroller.cpp
    colormapviewportplotcontroller.h
    colormapviewportplotcontroller.cpp
    colorscaleplotcontroller.h
    colorscaleplotcontroller.cpp
    customplotutils.h
    customplotutils.cpp
    graphcanvas.h
    graphcanvas.cpp
    graphplotcontroller.h
    graphplotcontroller.cpp
    data1dplotcontroller.h
    data2dplotcontroller.cpp
    data2dplotcontroller.h
    data1dplotcontroller.cpp
    graphviewportplotcontroller.h
    graphviewportplotcontroller.cpp
    viewportaxisplotcontroller.h
    viewportaxisplotcontroller.cpp
)

target_include_directories(${library_name}
    PUBLIC
        $<INSTALL_INTERFACE:public>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)
