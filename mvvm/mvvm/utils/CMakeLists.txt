set(library_name mvvm)

target_sources(${library_name} PRIVATE
    containerutils.cpp
    containerutils.h
    fileutils.cpp
    fileutils.h
    ifactory.h
    numericutils.cpp
    numericutils.h
    reallimits.cpp
    reallimits.h
    stringutils.cpp
    stringutils.h
)

target_include_directories(${library_name}
    PUBLIC
        $<INSTALL_INTERFACE:public>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)
