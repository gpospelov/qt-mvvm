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

#include <mvvm/core/export.h>
#include <string>
#include <vector>

namespace ModelView
{

namespace Utils
{

//! Returns true if file exists.
CORE_EXPORT bool exists(const std::string& fileName);

//! Joins two path elements into the path.
CORE_EXPORT std::string join(const std::string& part1, const std::string& part2);

//! Create directory, parent directory must exist. If path resolves to existing directory,
//! no error reported.
CORE_EXPORT bool create_directory(const std::string& path);

//! Removes directory with all its content.
CORE_EXPORT void remove_all(const std::string& path);

//! Creates directory in current working directory. If such directory already exists,
//! it will be removed with all its content.
// FIXME do not remove existing directory
CORE_EXPORT void create_dir(const std::string& dir_name);

//! Creates sub directory in given parent directory (should exist).
//! If sub-directory already exists, no action will be taken.
CORE_EXPORT void create_subdir(const std::string& parentName, const std::string& subdirName);

//! Removes recursively directory with given name. Directory name is relative
//! to the parent (working directory of the executable).
CORE_EXPORT bool removeRecursively(const std::string& dirname);

//! Returns list of files with given extention found in given directory.
CORE_EXPORT std::vector<std::string> FindFiles(const std::string& dirname, const std::string& ext);

} // namespace Utils

} // namespace ModelView

#endif // MVVM_UTILS_FILEUTILS_H
