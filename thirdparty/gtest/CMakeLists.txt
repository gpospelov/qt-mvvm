if(POLICY CMP0042)
    cmake_policy(SET CMP0042 NEW)
endif()

if( NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/googletest/.git" )
    message(SEND_ERROR "The git gtest submodule is not available, testing is not possible. "
        "Please run 'git submodule update --init --recursive'.")
else()
    if(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_VARIADIC_MAX=10 /wd4100 /wd4275")
    endif()

    option(INSTALL_GTEST "Enable installation of googletest. (Projects embedding googletest may want to turn this OFF.)" OFF)
    option(BUILD_SHARED_LIBS "Build shared libraries (DLLs)." ON)
    add_subdirectory(googletest)
endif()
