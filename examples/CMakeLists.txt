# CMakeLists.txt with user examples

if (MVVM_BUILD_EXAMPLES)
    add_subdirectory(helloworld)
    add_subdirectory(celleditors)
    add_subdirectory(collidingmice)
    add_subdirectory(concurrentplot)
    add_subdirectory(dragandmove)
    add_subdirectory(flateditor)
    add_subdirectory(graphicsproxy)
    add_subdirectory(layereditor)
    add_subdirectory(plotcolormap)
    add_subdirectory(plotgraphs)
    add_subdirectory(saveloadproject)
    add_subdirectory(treeviews)
    add_subdirectory(modelinqml)
endif()

install(DIRECTORY ${CMAKE_SOURCE_DIR}/examples DESTINATION share/mvvm)



