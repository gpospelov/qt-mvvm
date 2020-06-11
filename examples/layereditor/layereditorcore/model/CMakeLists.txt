set(library_name layereditorcore)

target_sources(${library_name} PRIVATE
    ApplicationModels.cpp
    ApplicationModels.h
    item_constants.h
    LayerItems.cpp
    LayerItems.h
    MaterialItems.cpp
    MaterialItems.h
    MaterialModel.cpp
    MaterialModel.h
    MaterialPropertyController.cpp
    MaterialPropertyController.h
    SampleModel.cpp
    SampleModel.h
)

target_include_directories(${library_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
