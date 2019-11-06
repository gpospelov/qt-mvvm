set(library_name mvvm_viewmodel)

if(WIN32)
    add_definitions(-DCORE_BUILD_DLL)
endif()

add_library(${library_name} SHARED "")

add_subdirectory(mvvm)

target_link_libraries(${library_name} PUBLIC mvvm_model Qt5::Widgets PRIVATE qcustomplot)

# to make clang code model in Qt creator happy
target_compile_features(${library_name} PUBLIC cxx_std_17)

target_include_directories(${library_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
