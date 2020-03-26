# Static library: quickreflcore.

target_sources(quickreflcore PRIVATE
    materialprofile.cpp
    materialprofile.h
    profilehelper.cpp
    profilehelper.h
    quicksimcontroller.cpp
    quicksimcontroller.h
    quicksimeditor.cpp
    quicksimeditor.h
    slice.h
    speculartoysimulation.cpp
    speculartoysimulation.h
)

target_include_directories(quickreflcore PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
