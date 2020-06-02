set(library_name quickreflcore)

target_sources(${library_name} PRIVATE
    openprojectwidget.cpp
    openprojectwidget.h
    projectmanagerinteractor.cpp
    projectmanagerinteractor.h
    projectpanewidget.cpp
    projectpanewidget.h
    recentprojectwidget.cpp
    recentprojectwidget.h
    welcomeview.cpp
    welcomeview.h
    welcomeviewsettings.cpp
    welcomeviewsettings.h
)

target_include_directories(${library_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
