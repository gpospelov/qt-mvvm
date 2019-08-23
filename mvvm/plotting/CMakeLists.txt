set(library_name mvvm)

target_sources(${library_name} PRIVATE
    axisplotcontrollers.h
    axisplotcontrollers.cpp
    graphcanvas.h
    graphcanvas.cpp
    graphitemcontroller.h
    graphitemcontroller.cpp
    itemcontroller.h
    itemcontroller.cpp
)

target_include_directories(${library_name}
    PUBLIC
        $<INSTALL_INTERFACE:public>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)
