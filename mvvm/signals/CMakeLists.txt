set(library_name mvvm)

target_sources(${library_name} PRIVATE
    callback_types.h
    callbackcontainer.h
    itemcontroller.cpp
    itemcontroller.h
    itemmapper.cpp
    itemmapper.h
    modelmapper.cpp
    modelmapper.h
    modelmapperinterface.h
)

target_include_directories(${library_name}
    PUBLIC
        $<INSTALL_INTERFACE:public>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)
