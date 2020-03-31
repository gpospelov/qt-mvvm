# Static library: quickreflcore.

target_sources(quickreflcore PRIVATE
    grapheditor.cpp
    grapheditor.h
    grapheditortoolbar.cpp
    grapheditortoolbar.h
)

target_include_directories(quickreflcore PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
