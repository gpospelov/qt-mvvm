# -----------------------------------------------------------------------------
# Library: mvvm_viewmodel
# -----------------------------------------------------------------------------
add_library(mvvm_viewmodel SHARED "")

add_subdirectory(mvvm)

target_link_libraries(mvvm_viewmodel PUBLIC mvvm_model Qt5::Widgets PRIVATE qcustomplot)
target_include_directories(mvvm_viewmodel PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)

# to make clang code model in Qt creator happy
target_compile_features(mvvm_viewmodel PUBLIC cxx_std_17)
