# Executable: quickrefl

add_subdirectory(libsaveloadproject)

add_executable(saveloadproject main.cpp)
target_link_libraries(saveloadproject PRIVATE saveloadprojectcore)
