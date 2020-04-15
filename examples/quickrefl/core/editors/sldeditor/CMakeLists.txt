set(library_name quickreflcore)

target_sources(${library_name} PRIVATE
    sldelementmodel.h
    sldelementmodel.cpp
    layerelementcontroller.h
    layerelementcontroller.cpp
    layerelementitem.h
    layerelementitem.cpp
    sldelementcontroller.cpp
    sldelementcontroller.h
    elementview.h
    elementview.cpp
    segmentelementview.h
    segmentelementview.cpp
    handleelementview.h
    handleelementview.cpp
    roughnesselementview.h
    roughnesselementview.cpp
    graphicsscene.cpp
    graphicsscene.h
    sldviewwidget.h
    sldviewwidget.cpp
    sldeditor.h
    sldeditor.cpp
)

target_include_directories(${library_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
