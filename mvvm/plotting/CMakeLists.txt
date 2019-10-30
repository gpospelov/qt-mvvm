set(library_name mvvm)

target_sources(${library_name} PRIVATE
    colormapcanvas.cpp
    colormapcanvas.h
    colormapinfoformatter.cpp
    colormapinfoformatter.h
    colormapplotcontroller.cpp
    colormapplotcontroller.h
    colormapviewportplotcontroller.cpp
    colormapviewportplotcontroller.h
    colorscaleplotcontroller.cpp
    colorscaleplotcontroller.h
    customplotutils.cpp
    customplotutils.h
    data1dplotcontroller.cpp
    data1dplotcontroller.h
    data2dplotcontroller.cpp
    data2dplotcontroller.h
    graphcanvas.cpp
    graphcanvas.h
    graphinfoformatter.cpp
    graphinfoformatter.h
    graphplotcontroller.cpp
    graphplotcontroller.h
    graphviewportplotcontroller.cpp
    graphviewportplotcontroller.h
    mousemovereporter.cpp
    mousemovereporter.h
    mouseposinfo.h
    statusstringformatterinterface.h
    statusstringreporter.cpp
    statusstringreporter.h
    statusstringreporterfactory.cpp
    statusstringreporterfactory.h
    viewportaxisplotcontroller.cpp
    viewportaxisplotcontroller.h
)

target_include_directories(${library_name}
    PUBLIC
        $<INSTALL_INTERFACE:public>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)
