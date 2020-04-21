set(library_name quickreflcore)

target_sources(${library_name} PRIVATE
    welcomeview.cpp
    welcomeview.h
    project.cpp
    project.h
    projectinterface.h
)

target_include_directories(${library_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
