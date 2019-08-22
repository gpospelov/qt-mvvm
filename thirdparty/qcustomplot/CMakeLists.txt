############################################################################
# CMakeLists.txt file for building qcustomplot static library
############################################################################
set(library_name qcustomplot)

set(CMAKE_AUTOMOC ON)
add_library(${library_name} STATIC qcustomplot.h qcustomplot.cpp)
target_link_libraries(${library_name} PUBLIC Qt5::Widgets Qt5::PrintSupport)
target_include_directories(${library_name} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
