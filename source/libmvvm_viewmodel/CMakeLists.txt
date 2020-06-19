# Library: mvvm_viewmodel

set(library_name mvvm_viewmodel)

set(CMAKE_AUTOMOC ON)

add_library(${library_name} SHARED "")

add_subdirectory(mvvm)

target_link_libraries(${library_name} PUBLIC mvvm_model Qt5::Widgets)
target_include_directories(${library_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)

# to make clang code model in Qt creator happy
target_compile_features(${library_name} PUBLIC cxx_std_17)
