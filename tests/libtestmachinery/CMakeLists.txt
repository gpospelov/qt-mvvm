set(library_name testmachinery)

file(GLOB source_files "*.cpp")
file(GLOB include_files "*.h")

add_library(${library_name} STATIC ${source_files} ${include_files})
target_link_libraries(${library_name} PUBLIC GTest::gtest GTest::gmock Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Test mvvm_model)
target_include_directories(${library_name} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}> $<BUILD_INTERFACE:${MVVM_AUTOGEN_DIR}>)

target_compile_features(${library_name} PUBLIC cxx_std_17)
