set(test testview)

file(GLOB source_files "*.cpp")
file(GLOB include_files "*.h")

find_package(Qt5Core REQUIRED)
find_package(Qt5Test REQUIRED)

# necessary for Qt creator and clang code model
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(CMAKE_AUTOMOC ON)
add_executable(${test} ${source_files} ${include_files})
target_link_libraries(${test} gtest gmock Qt5::Core Qt5::Test mvvm_view testmachinery qcustomplot)

if (MVVM_DISCOVER_TESTS)
    gtest_discover_tests(${test})
else()
    add_custom_target(${test}_run ALL DEPENDS ${test} COMMAND ${test})
endif()
