# Library: mvvm_model
set(library_name mvvm_model)
add_library(${library_name} SHARED "")

add_subdirectory(mvvm)

target_link_libraries(${library_name} PUBLIC Qt5::Widgets Threads::Threads)

target_include_directories(${library_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)

# to make clang code model in Qt creator happy
target_compile_features(${library_name} PUBLIC cxx_std_17)

if (MVVM_ENABLE_FILESYSTEM)
    add_definitions(-DENABLE_FILESYSTEM)
endif()

generate_export_header(${library_name})
