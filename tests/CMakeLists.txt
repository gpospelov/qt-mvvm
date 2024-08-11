enable_testing()

find_package(GTest 1.10 QUIET CONFIG)

include(GoogleTest)

if(WIN32)
    add_definitions(-DGTEST_LINKED_AS_SHARED_LIBRARY)
endif()

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core Test REQUIRED)
find_package(Threads)

add_subdirectory(libtestmachinery)
add_subdirectory(testintegration)
add_subdirectory(testmodel)
add_subdirectory(testview)
add_subdirectory(testviewmodel)

