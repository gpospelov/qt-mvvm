// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_UTILS_FILEUTILS_H
#define MVVM_UTILS_FILEUTILS_H

#include "mvvm/model_export.h"
#include <string>
#include <vector>

namespace ModelView::Utils {

//! Returns true if file exists.
MVVM_MODEL_EXPORT bool exists(const std::string& fileName);

//! Joins two path elements into the path.
MVVM_MODEL_EXPORT std::string join(const std::string& part1, const std::string& part2);

//! Create directory, parent directory must exist. If path resolves to existing directory,
//! no error reported.
MVVM_MODEL_EXPORT bool create_directory(const std::string& path);

//! Removes file or empty directory.
MVVM_MODEL_EXPORT bool remove(const std::string& path);

//! Removes directory with all its content.
MVVM_MODEL_EXPORT void remove_all(const std::string& path);

//! Provide the filename of a file path.
MVVM_MODEL_EXPORT std::string base_name(const std::string& path);

//! Returns list of files with given extention found in given directory.
MVVM_MODEL_EXPORT std::vector<std::string> FindFiles(const std::string& dirname,
                                                     const std::string& ext);

//! Returns the path to the parent directory.
MVVM_MODEL_EXPORT std::string parent_path(const std::string& path);

//! Returns true if the file indicated by 'path' refers to empty file or directory.
MVVM_MODEL_EXPORT bool is_empty(const std::string& path);

} // namespace ModelView::Utils

#endif // MVVM_UTILS_FILEUTILS_H
