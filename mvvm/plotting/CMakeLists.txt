set(library_name mvvm)

target_sources(${library_name} PRIVATE
    graphcanvas.h
    graphcanvas.cpp
    axisplotcontrollers.h
    axisplotcontrollers.cpp
    itemcontroller.h
    itemcontroller.cpp
)

target_include_directories(${library_name}
    PUBLIC
        $<INSTALL_INTERFACE:public>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)
