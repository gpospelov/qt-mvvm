set(library_name testmachinery)

file(GLOB source_files "*.cpp")
file(GLOB include_files "*.h")

find_package(Qt5Core REQUIRED)
find_package(Qt5Test REQUIRED)

add_library(${library_name} STATIC ${source_files} ${include_files})
target_link_libraries(${library_name} gtest gmock Qt5::Core Qt5::Test mvvm_model)
target_include_directories(${library_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
target_compile_features(${library_name} PUBLIC cxx_std_17)
