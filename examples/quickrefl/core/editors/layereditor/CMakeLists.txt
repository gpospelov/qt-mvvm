# Static library: quickreflcore.

target_sources(quickreflcore PRIVATE
    customeditorfactory.cpp
    customeditorfactory.h
    layereditor.cpp
    layereditor.h
    layereditoractions.cpp
    layereditoractions.h
    layereditortoolbar.cpp
    layereditortoolbar.h
    layereditorwidget.cpp
    layereditorwidget.h
    layerselectionmodel.cpp
    layerselectionmodel.h
    layertreeview.cpp
    layertreeview.h
    layerviewmodel.cpp
    layerviewmodel.h
    layerviewmodelcontroller.cpp
    layerviewmodelcontroller.h
    externalpropertycomboeditor.cpp
    externalpropertycomboeditor.h
)

target_include_directories(quickreflcore PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
