# Static library: quickreflcore.

target_sources(quickreflcore PRIVATE
    dataselectionmodel.cpp
    dataselectionmodel.h
    importdataeditor.cpp
    importdataeditor.h
)

target_include_directories(quickreflcore PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)

add_subdirectory(famousloader)
