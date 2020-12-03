include(GoogleTest)

if(WIN32)
    add_definitions(-DGTEST_LINKED_AS_SHARED_LIBRARY)
endif()

add_subdirectory(libtestmachinery)
add_subdirectory(testintegration)
add_subdirectory(testmodel)
add_subdirectory(testview)
add_subdirectory(testviewmodel)

