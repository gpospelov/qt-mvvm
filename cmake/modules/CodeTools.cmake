# Collection of functions to set-up code beautification and analysis
include(ClangFormat)

# List of targets for project code beautification.
set(BEAUTIFICATION_TARGETS mvvm_model mvvm_viewmodel mvvm_view testmodel testviewmodel testview)
set(BEAUTIFICATION_EXAMPLES celleditorscore concurrentplotcore dragandmovecore flateditorcore
    graphicsproxycore layereditorcore plotcolormapcore plotgraphscore saveloadprojectcore treeviewscore)


# Defines new target for 'clangformat' to beautify whole project.
# Use 'make clangformat' or 'cmake --build . --target clangformat' to beautify the code.
# Beautification settings are located in .clang-format in project directory.

function(project_clangformat_setup)
    set(all_sources)
    foreach(target ${BEAUTIFICATION_TARGETS})
        get_target_property(target_sources ${target} SOURCES)
        list(APPEND all_sources ${target_sources})
    endforeach()
    # examples needs to add manualy target source dir to all names
    foreach(target ${BEAUTIFICATION_EXAMPLES})
        get_target_property(target_sources ${target} SOURCES)
        get_target_property(target_source_dir ${target} SOURCE_DIR)
        foreach(target ${target_sources})
            list(APPEND all_sources ${target_source_dir}/${target})
        endforeach()
    endforeach()
   clangformat_setup(${all_sources})
endfunction()


# Setups test coverage target.
# Use 'make codecoverage' or 'cmake --build . --target codecoverage' to beautify the code.
# Requires -DMVVM_GENERATE_COVERAGE=ON

function(project_testcoverage_setup)
    setup_target_for_coverage_lcov(NAME coverage
        EXECUTABLE ctest -j 4
        DEPENDENCIES testmodel testviewmodel testview testintegration
        EXCLUDE
            "${PROJECT_SOURCE_DIR}/thirdparty/*"
            "${PROJECT_SOURCE_DIR}/tests/*"
            "${PROJECT_SOURCE_DIR}/examples/*"
            "${PROJECT_SOURCE_DIR}/source/libmvvm_view/*"
            "**CompilerId*" "/usr/*"  "${CMAKE_BINARY_DIR}/*"
        )
endfunction()

# Setups targets for code processing.

function(project_codetools_setup)
    if (MVVM_SETUP_CLANGFORMAT)
        project_clangformat_setup()
    endif()
    if (MVVM_SETUP_CODECOVERAGE)
        project_testcoverage_setup()
    endif()
endfunction()
