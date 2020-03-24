# Static library: quickreflcore.

target_sources(quickreflcore PRIVATE
    quicksimeditor.cpp
    quicksimeditor.h
)

target_include_directories(quickreflcore PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
