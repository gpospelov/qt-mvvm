# Static library: quickreflcore.

target_sources(quickreflcore PRIVATE
    quicksimcontroller.cpp
    quicksimcontroller.h
    quicksimeditor.cpp
    quicksimeditor.h
    speculartoysimulation.cpp
    speculartoysimulation.h
)

target_include_directories(quickreflcore PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
