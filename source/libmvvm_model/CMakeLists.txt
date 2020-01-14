# -----------------------------------------------------------------------------
# Library: mvvm_model
# -----------------------------------------------------------------------------
add_library(mvvm_model SHARED "")

add_subdirectory(mvvm)

target_link_libraries(mvvm_model PUBLIC Qt5::Widgets PRIVATE qcustomplot)

target_include_directories(mvvm_model PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)

# to make clang code model in Qt creator happy
target_compile_features(mvvm_model PUBLIC cxx_std_17)
target_clangformat_setup(mvvm_model)
