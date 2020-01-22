set(CMAKE_AUTORCC ON)

target_sources(quickreflcore PRIVATE
    icons.qrc
    resources.h
)

target_include_directories(quickreflcore PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
