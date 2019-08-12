set(library_name mvvm)

target_sources(${library_name} PRIVATE
    itemstreeview.cpp
    itemstreeview.h
    propertyeditor.cpp
    propertyeditor.h
    scientificspinbox.cpp
    scientificspinbox.h
)

target_include_directories(${library_name}
    PUBLIC
        $<INSTALL_INTERFACE:public>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)
