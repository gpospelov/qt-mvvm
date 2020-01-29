set(library_name sldeditorcore)

target_sources(${library_name} PRIVATE
    HandleView.h
    HandleView.cpp
    SegmentView.h
    SegmentView.cpp
    ViewObject.h
    ViewObject.cpp
)

target_include_directories(${library_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
