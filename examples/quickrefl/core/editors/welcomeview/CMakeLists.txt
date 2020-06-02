set(library_name quickreflcore)

target_sources(${library_name} PRIVATE
    modelhaschangedcontroller.cpp
    modelhaschangedcontroller.h
    openprojectwidget.cpp
    openprojectwidget.h
    project.cpp
    project.h
    project_types.h
    projectchangecontroller.cpp
    projectchangecontroller.h
    projectmanager.cpp
    projectmanager.h
    projectmanagerdecorator.cpp
    projectmanagerdecorator.h
    projectmanagerinteractor.cpp
    projectmanagerinteractor.h
    projectpanewidget.cpp
    projectpanewidget.h
    projectutils.cpp
    projectutils.h
    recentprojectwidget.cpp
    recentprojectwidget.h
    welcomeview.cpp
    welcomeview.h
    welcomeviewsettings.cpp
    welcomeviewsettings.h
)

target_include_directories(${library_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
