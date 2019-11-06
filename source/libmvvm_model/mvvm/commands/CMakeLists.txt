set(library_name mvvm)

target_sources(${library_name} PRIVATE
    abstractitemcommand.cpp
    abstractitemcommand.h
    commandadapter.cpp
    commandadapter.h
    commandservice.cpp
    commandservice.h
    copyitemcommand.cpp
    copyitemcommand.h
    insertnewitemcommand.cpp
    insertnewitemcommand.h
    moveitemcommand.cpp
    moveitemcommand.h
    removeitemcommand.cpp
    removeitemcommand.h
    setvaluecommand.cpp
    setvaluecommand.h
)
