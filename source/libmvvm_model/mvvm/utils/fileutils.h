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

//! Removes file or empty directory.
CORE_EXPORT bool remove(const std::string& path);

//! Removes directory with all its content.
CORE_EXPORT void remove_all(const std::string& path);

//! Provide the filename of a file path.
CORE_EXPORT std::string base_name(const std::string& path);

//! Returns list of files with given extention found in given directory.
CORE_EXPORT std::vector<std::string> FindFiles(const std::string& dirname, const std::string& ext);

} // namespace Utils

} // namespace ModelView

#endif // MVVM_UTILS_FILEUTILS_H
