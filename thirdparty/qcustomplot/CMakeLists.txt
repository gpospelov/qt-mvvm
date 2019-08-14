############################################################################
# CMakeLists.txt file for building qcustomplot static library
############################################################################
set(library_name qcustomplot)

set(CMAKE_AUTOMOC ON)
add_library(${library_name} STATIC qcustomplot.h qcustomplot.cpp)
target_link_libraries(${library_name} Qt5::Widgets)
