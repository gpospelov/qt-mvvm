set(library_name quickreflcore)

target_sources(${library_name} PRIVATE
    sldelementmodel.h
    sldelementmodel.cpp
    layerelementcontroller.h
    layerelementcontroller.cpp
    layerelementitem.h
    layerelementitem.cpp
    segmentelementview.h
    segmentelementview.cpp

    HandleView.h
    HandleView.cpp
    SegmentView.h
    SegmentView.cpp
    ViewObject.h
    ViewObject.cpp
    SegmentView.h
    SegmentView.cpp
    RoughnessView.h
    RoughnessView.cpp
)

target_include_directories(${library_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
