# Library: mvvm_view

set(library_name mvvm_view)

set(CMAKE_AUTOMOC ON)

add_library(${library_name} SHARED "")

add_subdirectory(mvvm)

target_link_libraries(${library_name} PUBLIC mvvm_viewmodel Qt5::Widgets PRIVATE qcustomplot)
target_include_directories(${library_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)

# to make clang code model in Qt creator happy
target_compile_features(${library_name} PUBLIC cxx_std_17)

#include(GenerateExportHeader)
#generate_export_header(${library_name})
#install(TARGETS s${library_name} DESTINATION ${LIBRARY_INSTALL_DIR})
#install(FILES
# someclass.h
# ${PROJECT_BINARY_DIR}/somelib_export.h DESTINATION ${INCLUDE_INSTALL_DIR}
#)
