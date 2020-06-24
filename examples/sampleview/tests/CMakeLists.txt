set(test testsampleview)

include(GoogleTest)

file(GLOB source_files "*.cpp")
file(GLOB include_files "*.h")

find_package(Qt5 COMPONENTS Widgets Core Test REQUIRED)

if(WIN32)
    add_definitions(-DGTEST_LINKED_AS_SHARED_LIBRARY)
endif()

# necessary for Qt creator and clang code model
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(CMAKE_AUTOMOC ON)
add_executable(${test} ${source_files} ${include_files})
target_link_libraries(${test} gtest gmock Qt5::Core Qt5::Test sampleview_core testmachinery)

# to make clang code model in Qt creator happy
target_compile_features(${test} PUBLIC cxx_std_17)

if (MVVM_DISCOVER_TESTS)
    gtest_discover_tests(${test})
else()
    add_custom_target(${test}_run ALL DEPENDS ${test} COMMAND ${test})
endif()
