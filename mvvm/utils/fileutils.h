// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <string>

namespace Utils {

//! Returns true if file exists.
bool exists(const std::string& fileName);

//! Creates directory in current working directory. If such directory already exists,
//! it will be removed with all its content.
void create_dir(const std::string& dir_name);

//! Creates sub directory in given parent directory (should exist).
//! If sub-directory already exists, no action will be taken.
void create_subdir(const std::string& parentName, const std::string& subdirName);

//! Removes recursively directory with given name. Directory name is relative
//! to the parent (working directory of the executable).
bool removeRecursively(const std::string& dirname);

}

#endif
