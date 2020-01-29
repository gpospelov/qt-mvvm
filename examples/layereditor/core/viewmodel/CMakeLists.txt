set(library_name layereditorcore)

target_sources(${library_name} PRIVATE
    CustomEditorFactory.cpp
    CustomEditorFactory.h
    CustomModelDelegate.cpp
    CustomModelDelegate.h
    LayerTableViewModelController.cpp
    LayerTableViewModelController.h
    LayerTableViewModel.cpp
    LayerTableViewModel.h
    MaterialTableViewModel.cpp
    MaterialTableViewModel.h
)

target_include_directories(${library_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
