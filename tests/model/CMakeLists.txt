set(test testmodel)

include(GoogleTest)

file(GLOB source_files "*.cpp")
file(GLOB include_files "*.h")

find_package(Qt5Core REQUIRED)
find_package(Qt5Test REQUIRED)

if(WIN32)
    add_definitions(-DGTEST_LINKED_AS_SHARED_LIBRARY)
endif()

set(CMAKE_AUTOMOC ON)
add_executable(${test} ${source_files} ${include_files})
target_link_libraries(${test} gtest gmock Qt5::Core Qt5::Test mvvm toyitems testmachinery)

# Manually adding directories with private API
message(INFO "XXX" ${MVVM_PRIVATE_API})
target_include_directories(${test} PRIVATE ${MVVM_PRIVATE_API})

if (MVVM_TESTS_AUTOEXEC)
    if (MVVM_TESTS_AUTODISCOVERY)
        gtest_discover_tests(${test})
    else()
        add_custom_target(${test}_run ALL DEPENDS ${test} COMMAND ${test})
    endif()
endif()
