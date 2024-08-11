enable_testing()

find_package(GTest 1.10 QUIET CONFIG)
if (NOT GTest_FOUND)
  message(WARNING "GTest with version >= \"1.10\" was not found, fetching from internet" )
  fetch_googletest()
endif()
find_package_message(
  GTest_DETAILS
  "Found GTest: ${GTest_DIR} (version \"${GTest_VERSION}\")"
  "[${GTest_FOUND}][${GTest_DIR}][v${GTest_VERSION}]")

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

