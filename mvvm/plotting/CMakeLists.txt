set(library_name mvvm)

target_sources(${library_name} PRIVATE
    axisplotcontrollers.h
    axisplotcontrollers.cpp
    graphcanvas.h
    graphcanvas.cpp
    graphplotcontroller.h
    graphplotcontroller.cpp
    itemcontroller.h
    itemcontroller.cpp
    data1dplotcontroller.h
    data1dplotcontroller.cpp
    graphviewportplotcontroller.h
    graphviewportplotcontroller.cpp
)

target_include_directories(${library_name}
    PUBLIC
        $<INSTALL_INTERFACE:public>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)
