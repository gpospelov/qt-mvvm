set(library_name sldeditorcore)

target_sources(${library_name} PRIVATE
    AppModels.cpp
    AppModels.h
    ViewItemsModel.cpp
    ViewItemsModel.h
    HandleItem.h
    HandleItem.cpp    
)

target_include_directories(${library_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
