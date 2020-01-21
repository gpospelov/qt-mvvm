# Static library: quickreflcore.

target_sources(quickreflcore PRIVATE
    materialeditor.cpp
    materialeditor.h
    materialeditoractions.cpp
    materialeditoractions.h
    materialeditortoolbar.cpp
    materialeditortoolbar.h
    materialtableview.cpp
    materialtableview.h
    styleutils.cpp
    styleutils.h
)

target_include_directories(quickreflcore PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
