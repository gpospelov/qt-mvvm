set(library_name sldeditorcore)

target_sources(${library_name} PRIVATE
    ApplicationModels.cpp
    ApplicationModels.h
    ViewItemsModel.cpp
    ViewItemsModel.h
)

target_include_directories(${library_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
