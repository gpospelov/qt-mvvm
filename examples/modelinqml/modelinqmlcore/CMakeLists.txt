# library: flateditorcore
set(library_name modelinqmlcore)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_library(${library_name} SHARED "")
target_link_libraries(${library_name} PRIVATE MVVM::View Qt5::Qml)

target_sources(${library_name} PRIVATE
    tablemodel.h
    backend.cpp
    backend.h
    modelinqmlcore.qrc
    particlemodel.cpp
    particlemodel.h
)

# During plugin searching Qt will be looking for 'qmldir' file
# So we should place it next to our plugin lib.
add_custom_command(
    TARGET modelinqmlcore
    POST_BUILD
    COMMAND
        ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_LIST_DIR}/qmldir
        $<TARGET_FILE_DIR:modelinqmlcore>/qmldir
)

target_include_directories(${library_name} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/..)
