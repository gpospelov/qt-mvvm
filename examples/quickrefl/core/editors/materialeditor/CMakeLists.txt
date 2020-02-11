# Static library: quickreflcore.

target_sources(quickreflcore PRIVATE
    materialeditor.cpp
    materialeditor.h
    materialeditoractions.cpp
    materialeditoractions.h
    materialeditortoolbar.cpp
    materialeditortoolbar.h
    materialeditorwidget.cpp
    materialeditorwidget.h
    materialselectionmodel.cpp
    materialselectionmodel.h
    materialtableview.cpp
    materialtableview.h
    materialtreeview.cpp
    materialtreeview.h
)

target_include_directories(quickreflcore PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
