# Static library: quickreflcore.

target_sources(quickreflcore PRIVATE
    importdataeditor.cpp
    importdataeditor.h
)

target_include_directories(quickreflcore PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
