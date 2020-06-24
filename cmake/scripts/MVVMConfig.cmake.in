#  MVVM_INCLUDE_DIRS - include directories for qt-mvvm
#  MVVM_LIBRARIES    - libraries to link against

get_filename_component(MVVM_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)

include(CMakeFindDependencyMacro)
find_dependency(Qt5 5.12 COMPONENTS Widgets REQUIRED)
find_dependency(Threads)

if(TARGET MVVM::Model OR TARGET MVVM::ViewModel OR TARGET MVVM::View)
else()
    message(STATUS "MVVMConfig.cmake including ${MVVM_CMAKE_DIR}/MVVMTargets.cmake")
   include("${MVVM_CMAKE_DIR}/MVVMTargets.cmake")
endif()

set(MVVM_LIBRARIES MVVM::Model MVVM::ViewModel MVVM::View)

message(STATUS "MVVMConfig.cmake in ${CMAKE_CURRENT_LIST_FILE}")
message(STATUS " MVVM_LIBRARIES ${MVVM_LIBRARIES}")


