# Static library: quickreflcore.

target_sources(quickreflcore PRIVATE
    materialeditor.cpp
    materialeditor.h
    styleutils.h
    styleutils.cpp
)

target_include_directories(quickreflcore PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
