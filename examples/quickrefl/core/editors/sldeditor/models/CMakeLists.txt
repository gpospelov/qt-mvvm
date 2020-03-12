set(library_name quickreflcore)

target_sources(${library_name} PRIVATE
    SLDViewModel.cpp
    SLDViewModel.h
    SLDController.cpp
    SLDController.h
    HandleItem.h
    HandleItem.cpp   
    SegmentItem.h
    SegmentItem.cpp
    RoughnessViewItem.h
    RoughnessViewItem.cpp
)

target_include_directories(${library_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
