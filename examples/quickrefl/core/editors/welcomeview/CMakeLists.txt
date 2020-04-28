set(library_name quickreflcore)

target_sources(${library_name} PRIVATE
    project.cpp
    project.h
    projectinterface.h
    projectmanager.cpp
    projectmanager.h
    projectmanagerinterface.h
    projectutils.cpp
    projectutils.h
    welcomeview.cpp
    welcomeview.h
)

target_include_directories(${library_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
