set(library_name mvvm)

target_sources(${library_name} PRIVATE
    callbackcontainer.h
    itemmapper.cpp
    itemmapper.h
    modelmapper.cpp
    modelmapper.h)

target_include_directories(${library_name}
    PUBLIC
        $<INSTALL_INTERFACE:public>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)
