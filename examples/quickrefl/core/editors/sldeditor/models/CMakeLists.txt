set(library_name quickreflcore)

target_sources(${library_name} PRIVATE
    SLDViewModel.cpp
    SLDViewModel.h
    HandleItem.h
    HandleItem.cpp   
    SegmentItem.h
    SegmentItem.cpp
    RoughnessItem.h
    RoughnessItem.cpp
)

target_include_directories(${library_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
