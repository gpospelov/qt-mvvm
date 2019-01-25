set(test testviewmodel)

include(GoogleTest)

file(GLOB source_files "*.cpp")
file(GLOB include_files "*.h")

find_package(Qt5Core REQUIRED)
find_package(Qt5Test REQUIRED)

include_directories(${BUILD_INC_DIR} ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(CMAKE_AUTOMOC ON)
add_executable(${test} ${source_files} ${include_files})
target_link_libraries(${test} gtest Qt5::Core Qt5::Test mvvm toyitems testmachinery)

#add_custom_target(${test}_run ALL DEPENDS ${test} COMMAND ${test})
gtest_discover_tests(${test})
