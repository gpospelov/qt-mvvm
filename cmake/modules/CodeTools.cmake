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
